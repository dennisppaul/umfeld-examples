#pragma once
#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

/*
 * C++ Virtual Functions for Inheritance:
 * 
 * In the original Java version, methods are virtual by default, allowing
 * automatic polymorphism. In C++, we must explicitly declare methods as
 * 'virtual' to enable inheritance and method overriding.
 * 
 * Key points:
 * - virtual destructor: Essential for proper cleanup of derived objects
 * - virtual update(): Allows CrazyParticle to override with custom behavior
 * - virtual display(): Allows CrazyParticle to add rotating line graphics
 * 
 * Without these virtual keywords, CrazyParticle would not properly override
 * the base class methods when stored in a polymorphic container.
 */

// A simple Particle class

class Particle {
public:
    PVector position;
    PVector velocity;
    PVector acceleration;
    float   lifespan;

    // default constructor
    Particle() : position(0,0,0), velocity(0,0,0), acceleration(0,0,0), lifespan(255) {}

    Particle(PVector l) {
        acceleration = PVector(0, 0.05);
        velocity     = PVector(random(-1, 1), random(-2, 0));
        position     = l.copy();
        lifespan     = 255.0;
    }

    virtual ~Particle() {} // Virtual destructor for proper cleanup

    void run() {
        update();
        display();
    }

    // Method to update position - make virtual for inheritance
    virtual void update() {
        velocity.add(acceleration);
        position.add(velocity);
        lifespan -= 2.0;
    }

    // Method to display - make virtual for inheritance
    virtual void display() {
        stroke(1.f, lifespan/255.f); //@diff(color_range)
        fill(1.f, lifespan/255.f); //@diff(color_range)
        ellipse(position.x, position.y, 8, 8);
    }

    // Is the particle still useful?
    bool isDead() {
        return (lifespan < 0.0);
    }
};