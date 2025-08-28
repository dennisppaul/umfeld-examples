#pragma once
#include "Umfeld.h"
#include "PVector.h"
/**
 * Forces (Gravity and Fluid Resistence) with Vectors 
 * by Daniel Shiffman.  
 * 
 * Demonstration of multiple force acting on bodies (Mover class)
 * Bodies experience gravity continuously
 * Bodies experience fluid resistance when in "water"
 */

using namespace umfeld;

class Mover {
public:
    // position, velocity, and acceleration
    PVector position;
    PVector velocity;
    PVector acceleration;

    // Mass is tied to size
    float mass;

    // default constructor
    Mover() : mass(1), position(0, 0), velocity(0, 0), acceleration(0, 0) {}

    Mover(float m, float x, float y) {
        mass = m;
        position = PVector(x, y);
        velocity = PVector(0, 0);
        acceleration = PVector(0, 0);
    }

    // Newton's 2nd law: F = M * A
    // or A = F / M
    void applyForce(PVector force) {
        // Divide by mass
        PVector f = PVector::div(force, mass);
        // Accumulate all forces in acceleration
        acceleration.add(f);
    }

    void update() {
        // Velocity changes according to acceleration
        velocity.add(acceleration);
        // position changes by velocity
        position.add(velocity);
        // We must clear acceleration each frame
        acceleration.mult(0);
    }

    // Draw Mover
    void display() {
        stroke(1.f); //@diff(color_range)
        strokeWeight(2);
        fill(1.f, .78f); //@diff(color_range)
        ellipse(position.x, position.y, mass * 16, mass * 16);
    }

    // Bounce off bottom of window
    void checkEdges() {
        if (position.y > height) {
            velocity.y *= -0.9; // A little dampening when hitting the bottom
            position.y = height;
        }
    }
};
