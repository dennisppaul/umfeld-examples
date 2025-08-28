#pragma once
#include "Umfeld.h"
#include "PVector.h"
#include "Particle.h"

using namespace umfeld;

// A class to describe a group of Particles
// An ArrayList is used to manage the list of Particles

class ParticleSystem {

    std::vector<Particle> particles; // A vector for all the particles
    PVector origin;    // An origin point for where particles are birthed
    PImage* img;
public:

    // default constructor
    ParticleSystem() : origin(0, 0), img(nullptr) {}

    ParticleSystem(int num, PVector v, PImage* img_) {
        particles.reserve(num); // Reserve space for particles
        origin = v.copy();                  // Store the origin point
        img = img_;
        for (int i = 0; i < num; i++) {
            particles.push_back(Particle(origin, img)); // Add "num" amount of particles to the vector
        }
    }

    void run() {
        for (int i = particles.size() - 1; i >= 0; i--) {
            Particle& p = particles[i];
            p.run();
            if (p.isDead()) {
                particles.erase(particles.begin() + i);
            }
        }
    }

    // Method to add a force vector to all particles currently in the system
    void applyForce(PVector dir) {
        // Enhanced loop!!!
        for (Particle& p: particles) {
            p.applyForce(dir);
        }
    }

    void addParticle() {
        particles.push_back(Particle(origin, img));
    }
};