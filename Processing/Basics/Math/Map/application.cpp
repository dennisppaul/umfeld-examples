/**
 * Map.
 * 
 * Use the map() function to take any number and scale it to a new number 
 * that is more useful for the project that you are working on. For example, use the
 * numbers from the mouse position to control the size or color of a shape. 
 * In this example, the mouse’s x-coordinate (numbers between 0 and 360) are scaled to
 * new numbers to define the color and size of a circle.
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
}

void draw() {
    background(0.f);
    // Scale the mouseX value from 0 to 640 to a range between 0 and 0.68
    float c = map(mouseX, 0, width, 0, 0.68f); //@diff(color_range)
    // Scale the mouseX value from 0 to 640 to a range between 40 and 300
    float d = map(mouseX, 0, width, 40, 300);
    fill(1.f, c, 0); //@diff(color_range)
    ellipse(width / 2, height / 2, d, d);
}
