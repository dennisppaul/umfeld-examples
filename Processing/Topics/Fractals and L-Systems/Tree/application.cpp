/**
 * Recursive Tree
 * by Daniel Shiffman.  
 * 
 * Renders a simple tree-like structure via recursion. 
 * The branching angle is calculated as a function of 
 * the horizontal mouse location. Move the mouse left
 * and right to change the angle.
 */
#include "Umfeld.h"

using namespace umfeld;

float theta;

void branch(float h); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
}

void draw() {
    background(0.f); //@diff(color_range)
    set_frame_rate(30);
    stroke(1.f); //@diff(color_range)
    // Let's pick an angle 0 to 90 degrees based on the mouse position
    float a = (mouseX / (float) width) * 90.f;
    // Convert it to radians
    theta = radians(a);
    // Start the tree from the bottom of the screen
    translate(width / 2, height);
    // Draw a line 120 pixels
    line(0, 0, 0, -120);
    // Move to the end of that line
    translate(0, -120);
    // Start the recursive branching!
    branch(120);
}

void branch(float h) {
    // Each branch will be 2/3rds the size of the previous one
    h *= 0.66;

    // All recursive functions must have an exit condition!!!!
    // Here, ours is when the length of the branch is 2 pixels or less
    if (h > 2) {
        pushMatrix();      // Save the current state of transformation (i.e. where are we now)
        rotate(theta);     // Rotate by theta
        line(0, 0, 0, -h); // Draw the branch
        translate(0, -h);  // Move to the end of the branch
        branch(h);         // Ok, now call myself to draw two new branches!!
        popMatrix();       // Whenever we get back here, we "pop" in order to restore the previous matrix state

        // Repeat the same thing, only branch off to the "left" this time!
        pushMatrix();
        rotate(-theta);
        line(0, 0, 0, -h);
        translate(0, -h);
        branch(h);
        popMatrix();
    }
}
