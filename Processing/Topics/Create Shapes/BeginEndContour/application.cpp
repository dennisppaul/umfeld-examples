/**
 * BeginEndContour
 * 
 * How to cut a shape out of another using beginContour() and endContour()
 */
#include "Umfeld.h"

using namespace umfeld;

// PShape s; //unimplemented

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {

    // Make a shape
    // s = createShape();
    // // s.beginShape();
    // s.fill(0);
    // s.stroke(255);
    // s.strokeWeight(2);
    // // Exterior part of shape
    // s.vertex(-100, -100);
    // s.vertex(100, -100);
    // s.vertex(100, 100);
    // s.vertex(-100, 100);

    // // Interior part of shape
    // s.beginContour();
    // s.vertex(-10, -10);
    // s.vertex(-10, 10);
    // s.vertex(10, 10);
    // s.vertex(10, -10);
    // s.endContour();

    // Finishing off shape
    // s.endShape(CLOSE);
}

void draw() {
    background(.2f); //@diff(color_range)
    // Display shape
    translate(width / 2, height / 2);
    // Shapes can be rotated
    // s.rotate(0.01);
    // shape(s);
}
