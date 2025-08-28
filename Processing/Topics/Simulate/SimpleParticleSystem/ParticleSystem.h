#pragma once
#include "Umfeld.h"
#include "PVector.h"
#include "Particle.h"

using namespace umfeld;

// A class to describe a group of Particles
// An ArrayList is used to manage the list of Particles

class ParticleSystem {
    std::vector<Particle> particles;
    PVector origin;

public:

    //default constructor
    ParticleSystem() : origin(PVector(0, 0)), particles(std::vector<Particle>()) {}

    ParticleSystem(const PVector& position) {
        origin    = position.copy();
        particles = std::vector<Particle>();
    }

    void addParticle() {
        particles.push_back(Particle(origin));
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
};