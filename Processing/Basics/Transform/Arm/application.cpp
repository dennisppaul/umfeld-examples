/**
 * Arm. 
 * 
 * The angle of each segment is controlled with the mouseX and
 * mouseY position. The transformations applied to the first segment
 * are also applied to the second segment because they are inside
 * the same pushMatrix() and popMatrix() group.
*/
#include "Umfeld.h"

using namespace umfeld;

float x, y;
float angle1    = 0.0;
float angle2    = 0.0;
float segLength = 100;

void segment(float x, float y, float a); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    strokeWeight(30);
    stroke(1.f, .62f); //@diff(color_range)

    x = width * 0.3;
    y = height * 0.5;
}

void draw() {
    background(0.f); //@diff(color_range)

    angle1 = (mouseX / float(width) - 0.5) * -PI;
    angle2 = (mouseY / float(height) - 0.5) * PI;

    pushMatrix();
    segment(x, y, angle1);
    segment(segLength, 0, angle2);
    popMatrix();
}

void segment(float x, float y, float a) {
    translate(x, y);
    rotate(a);
    line(0, 0, segLength, 0);
}
