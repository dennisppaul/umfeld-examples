/**
 * Follow 3  
 * based on code from Keith Peters. 
 * 
 * A segmented line follows the mouse. The relative angle from
 * each segment to the next is calculated with atan2() and the
 * position of the next is calculated with sin() and cos().
 */
#include "Umfeld.h"

using namespace umfeld;

std::vector<float> x(20); //@diff(std::vector)
std::vector<float> y(20); //@diff(std::vector)
float segLength = 18;

void dragSegment(int i, float xin, float yin); //@diff(forward_declaration)
void segment(float x, float y, float a); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    strokeWeight(9);
    stroke(1.f, .39f); //@diff(color_range)
}

void draw() {
    background(0.f); //@diff(color_range)
    dragSegment(0, mouseX, mouseY);
    for (int i = 0; i < x.size() - 1; i++) {
        dragSegment(i + 1, x[i], y[i]);
    }
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
