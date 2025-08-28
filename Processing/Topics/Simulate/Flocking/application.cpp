/**
 * Flocking 
 * by Daniel Shiffman.  
 * 
 * An implementation of Craig Reynold's Boids program to simulate
 * the flocking behavior of birds. Each boid steers itself based on 
 * rules of avoidance, alignment, and coherence.
 * 
 * Click the mouse to add a new boid.
 */

#include "Umfeld.h"
#include "Flock.h"

using namespace umfeld;

Flock flock;

void settings() {
    size(640, 360);
}

void setup() {
    // Add an initial set of boids into the system
    for (int i = 0; i < 150; i++) {
        flock.addBoid(Boid(width / 2, height / 2));
    }
}

void draw() {
    background(.19f); //@diff(color_range)
    flock.run();
}

// Add a new boid into the System
void mousePressed() {
    flock.addBoid(Boid(mouseX, mouseY));
}
