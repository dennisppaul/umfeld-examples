/**
 * Acceleration with Vectors 
 * by Daniel Shiffman.  
 * 
 * Demonstration of the basics of motion with vector.
 * A "Mover" object stores location, velocity, and acceleration as vectors
 * The motion is controlled by affecting the acceleration (in this case towards the mouse)
 */
#pragma once
#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

class Mover {

    // The Mover tracks location, velocity, and acceleration
    PVector location;
    PVector velocity;
    PVector acceleration;
    // The Mover's maximum speed
    float topspeed;

public:
    Mover() {
        // Start in the center
        location = PVector(width / 2, height / 2);
        velocity = PVector(0, 0);
        topspeed = 5;
    }

    void update() {

        // Compute a vector that points from location to mouse
        PVector mouse = PVector(mouseX, mouseY);
        PVector acceleration = PVector::sub(mouse, location);
        // Set magnitude of acceleration
        acceleration.setMag(0.2);

        // Velocity changes according to acceleration
        velocity.add(acceleration);
        // Limit the velocity by topspeed
        velocity.limit(topspeed);
        // Location changes by velocity
        location.add(velocity);
    }

    void display() {
        stroke(1.f); //@diff(color_range)
        strokeWeight(2);
        fill(.49f); //@diff(color_range)
        ellipse(location.x, location.y, 48, 48);
    }
};
