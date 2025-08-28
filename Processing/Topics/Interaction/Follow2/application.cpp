/**
 * Follow 2  
 * based on code from Keith Peters. 
 * 
 * A two-segmented arm follows the cursor position. The relative
 * angle between the segments is calculated with atan2() and the
 * position calculated with sin() and cos().
 */
#include "Umfeld.h"

using namespace umfeld;

std::vector<float> x(2);
std::vector<float> y(2);
float segLength = 50;

void segment(float x, float y, float a); //@diff(forward_declaration)
void dragSegment(int i, float xin, float yin); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    strokeWeight(20.0);
    stroke(1.f, .39f); //@diff(color_range)
}

void draw() {
    background(0.f); //@diff(color_range)
    dragSegment(0, mouseX, mouseY);
    dragSegment(1, x[0], y[0]);
}

void dragSegment(int i, float xin, float yin) {
    float dx    = xin - x[i];
    float dy    = yin - y[i];
    float angle = atan2(dy, dx);
    x[i]        = xin - cos(angle) * segLength;
    y[i]        = yin - sin(angle) * segLength;
    segment(x[i], y[i], angle);
}

void segment(float x, float y, float a) {
    pushMatrix();
    translate(x, y);
    rotate(a);
    line(0, 0, segLength, 0);
    popMatrix();
}
