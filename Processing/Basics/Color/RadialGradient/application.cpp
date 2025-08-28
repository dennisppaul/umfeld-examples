/**
 * Radial Gradient. 
 * 
 * Draws a series of concentric circles to create a gradient 
 * from one color to another.
 */

#include "Umfeld.h"
#include "glm/gtx/color_space.hpp"

using namespace umfeld;

int dim;

void drawGradient(float x, float y) {
    int radius = dim / 2;
    float h = random(0, 360);
    for (int r = radius; r > 0; --r) {
        glm::vec3 hsv(h, 90.f/100.f, 90.f/100.f);
        glm::vec3 rgb = glm::rgbColor(hsv);
        fill(rgb.r, rgb.g, rgb.b);
        ellipse(x, y, r, r);
        h = (int) (h + 1) % 360;
    }
}

void settings() {
    size(640, 360);
}

void setup() {
    dim = width / 2;
    background(0.f); //@diff(color_range)
    noStroke();
    ellipseMode(RADIUS);
    set_frame_rate(1.f); //@diff(frameRate)
}


void draw() {
    background(0.f); //@diff(color_range)
    for (int x = 0; x <= width; x += dim) {
        drawGradient(x, height / 2);
    }
}
