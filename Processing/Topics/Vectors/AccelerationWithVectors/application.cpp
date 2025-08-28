/**
 * Acceleration with Vectors 
 * by Daniel Shiffman.  
 * 
 * Demonstration of the basics of motion with vector.
 * A "Mover" object stores location, velocity, and 
 * acceleration as vectors. The motion is controlled by 
 * affecting the acceleration (in this case towards the mouse).
 */
#include "Umfeld.h"
#include "Mover.h"

using namespace umfeld;

// A Mover object
Mover mover;

void settings() {
    size(640, 360);
}

void setup() {
    mover = Mover();
}

void draw() {
    background(0.f); //@diff(color_range)

    // Update the location
    mover.update();
    // Display the Mover
    mover.display();
}
