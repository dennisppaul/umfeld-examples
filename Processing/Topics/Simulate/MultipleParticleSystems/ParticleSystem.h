#pragma once
#include "Umfeld.h"
#include "PVector.h"
#include "Particle.h"
#include "CrazyParticle.h"
#include <memory>

using namespace umfeld;

/*
 * C++ Inheritance and std::unique_ptr Explanation:
 * 
 * Key differences from Java:
 * 1. Object Slicing: In C++, storing derived objects (CrazyParticle) in a container
 *    of base objects (std::vector<Particle>) causes "object slicing" - the derived
 *    parts are lost, and only the base Particle behavior remains.
 * 
 * 2. std::unique_ptr Solution: We use std::unique_ptr<Particle> to store pointers
 *    to objects rather than the objects themselves. This preserves polymorphism:
 *    - std::unique_ptr automatically manages memory (no manual delete needed)
 *    - Polymorphism works correctly through pointer indirection
 *    - Virtual functions in base class enable proper method dispatch
 * 
 * 3. Virtual Functions: The base Particle class needs virtual update() and display()
 *    methods to allow CrazyParticle to override them properly(see CrazyParticle.h).
 * 
 * 4. Move Semantics: std::unique_ptr cannot be copied (only moved), so we need:
 *    - Move constructors and assignment operators for ParticleSystem
 *    - Reference-based iteration (ParticleSystem& ps) instead of copying
 * 
 * This approach maintains the same polymorphic behavior as the Java original
 * while following C++ best practices for memory management and inheritance.
 */

// A std::vector of unique_ptr<Particle> is used to manage the list of Particles

class ParticleSystem {
public:
    std::vector<std::unique_ptr<Particle>> particles; // Use smart pointers for polymorphism
    PVector origin;    // An origin point for where particles are birthed

    ParticleSystem(int num, PVector v) {
        particles = std::vector<std::unique_ptr<Particle>>(); // Initialize the vector
        origin = v.copy();                  // Store the origin point
        for (int i = 0; i < num; i++) {
            particles.push_back(std::make_unique<Particle>(origin)); // Add "num" amount of particles to the vector
        }
    }

    // Move constructor
    ParticleSystem(ParticleSystem&& other) noexcept 
        : particles(std::move(other.particles)), origin(std::move(other.origin)) {}

    // Move assignment operator
    ParticleSystem& operator=(ParticleSystem&& other) noexcept {
        if (this != &other) {
            particles = std::move(other.particles);
            origin = std::move(other.origin);
        }
        return *this;
    }

    // Delete copy constructor and copy assignment operator
    ParticleSystem(const ParticleSystem&) = delete;
    ParticleSystem& operator=(const ParticleSystem&) = delete;


    void run() {
        // Cycle through the vector backwards, because we are deleting while iterating
        for (int i = particles.size() - 1; i >= 0; i--) {
            Particle* p = particles[i].get();
            p->run();
            if (p->isDead()) {
                particles.erase(particles.begin() + i);
            }
        }
    }

    void addParticle() {
        std::unique_ptr<Particle> p;
        // Add either a Particle or CrazyParticle to the system
        if (int(random(0, 2)) == 0) {
            p = std::make_unique<Particle>(origin);
        } else {
            p = std::make_unique<CrazyParticle>(origin);
        }
        particles.push_back(std::move(p));
    }

    void addParticle(std::unique_ptr<Particle> p) {
        particles.push_back(std::move(p));
    }

    // A method to test if the particle system still has particles
    bool dead() {
        return particles.empty();
    }
};
