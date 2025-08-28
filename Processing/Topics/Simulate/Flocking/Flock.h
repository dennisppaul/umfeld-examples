#pragma once
#include "Umfeld.h"
#include "PVector.h"
#include "Boid.h"

using namespace umfeld;

// The Flock (a list of Boid objects)

class Flock {
    
    std::vector<Boid> boids; // A vector for all the boids

public:
    Flock() {
    }

    void run() {
        for (Boid& b: boids) {
            b.run(boids); // Passing the entire list of boids to each boid individually
        }
    }

    void addBoid(Boid b) {
        boids.push_back(b); //@diff(std::vector)
    }
};
