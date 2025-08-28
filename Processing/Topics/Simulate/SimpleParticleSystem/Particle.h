#pragma once
#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

// A simple Particle class

class Particle {
    PVector position;
    PVector velocity;
    PVector acceleration;
    float   lifespan;

public:
    Particle(PVector l) {
        acceleration = PVector(0, 0.05);
        velocity     = PVector(random(-1, 1), random(-2, 0));
        position     = l;
        lifespan     = 255.0;
    }

    void run() {
        update();
        display();
    }

    // Method to update position
    void update() {
        velocity.add(acceleration);
        position.add(velocity);
        lifespan -= 1.0;
    }

    // Method to display
    void display() {
        stroke(1.f, lifespan/255.f); //@diff(color_range)
        fill(1.f, lifespan/255.f); //@diff(color_range)
        ellipse(position.x, position.y, 8, 8);
    }

    // Is the particle still useful?
    bool isDead() {
        if (lifespan < 0.0) {
            return true;
        } else {
            return false;
        }
    }
};