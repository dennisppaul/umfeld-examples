/**
 * Vector 
 * by Daniel Shiffman.  
 * 
 * Demonstration of some basic vector math: subtraction, 
 * normalization, scaling. Normalizing a vector sets 
 * its length to 1.
 */
#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {

}

void draw() {
    background(0.f); //@diff(color_range)

    // A vector that points to the mouse location
    PVector mouse = PVector(mouseX, mouseY);

    // A vector that points to the center of the window
    PVector center = PVector(width / 2, height / 2);

    // Subtract center from mouse which results in a
    // vector that points from center to mouse
    mouse.sub(center);

    // Normalize the vector
    mouse.normalize();

    // Multiply its length by 150 (Scaling its length)
    mouse.mult(150);

    translate(width / 2, height / 2);
    // Draw the resulting vector
    stroke(1.f); //@diff(color_range)
    strokeWeight(4);
    line(0, 0, mouse.x, mouse.y);
}
