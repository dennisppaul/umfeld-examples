/**
 * Shape Primitives. 
 * 
 * The basic shape primitive functions are triangle(),
 * rect(), quad(), ellipse(), and arc(). Squares are made
 * with rect() and circles are made with ellipse(). Each 
 * of these functions requires a number of parameters to 
 * determine the shape's position and size. 
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
    noStroke();
}

void draw() {
    fill(0.8f); //@diff(color_range)
    triangle(18, 18, 0, 18, 360, 0, 81, 360, 0); //@diff(triangle)

    fill(0.4f); //@diff(color_range)
    rect(81, 81, 63, 63);

    fill(0.8f); //@diff(color_range)
    quad(189, 18, 0, 216, 18, 0, 216, 360, 0, 144, 360, 0); //@diff(quad)

    fill(1.0f); //@diff(color_range)
    ellipse(252, 144, 72, 72);

    fill(0.8f); //@diff(color_range)
    triangle(288, 18, 0, 351, 360, 0, 288, 360, 0); //@diff(triangle)

    fill(1.0f);
    arc(479, 300, 280, 280, PI, TWO_PI);
}
/*
note:
- triangle() and quad() can be 2D shapes,
  so to have a override for 2D coordinates arguments(without z), or even with glm::vecN might be meaningful.
*/