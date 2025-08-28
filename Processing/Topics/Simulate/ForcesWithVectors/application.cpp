/**
 * Forces (Gravity and Fluid Resistence) with Vectors
 * by Daniel Shiffman.
 *
 * Demonstration of multiple forces acting on bodies.
 * Bodies experience gravity continuously and fluid
 * resistance when in "water".
 */
#include "Umfeld.h"
#include "Liquid.h"
#include "Mover.h"

using namespace umfeld;

// Five moving bodies
std::vector<Mover> movers(10); //@diff(std::vector)

// Liquid
Liquid liquid;

void reset(); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    reset();
    // Create liquid object
    liquid = Liquid(0, height / 2, width, height / 2, 0.1);
}

void draw() {
    background(0.f); //@diff(color_range)

    // Draw water
    liquid.display();

    for (Mover& mover: movers) {

        // Is the Mover in the liquid?
        if (liquid.contains(mover)) {
            // Calculate drag force
            PVector drag = liquid.drag(mover);
            // Apply drag force to Mover
            mover.applyForce(drag);
        }

        // Gravity is scaled by mass here!
        PVector gravity = PVector(0, 0.1 * mover.mass);
        // Apply gravity
        mover.applyForce(gravity);

        // Update and display
        mover.update();
        mover.display();
        mover.checkEdges();
    }

    fill(1.f); //@diff(color_range)
    text("click mouse to reset", 10, 30);
}

void mousePressed() {
    reset();
}

// Restart all the Mover objects randomly
void reset() {
    for (int i = 0; i < movers.size(); i++) {
        movers[i] = Mover(random(0.5, 3), 40 + i * 70, 0);
    }
}