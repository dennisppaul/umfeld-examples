/**
 * Double Random 
 * by Ira Greenberg.  
 * 
 * Using two random() calls and the point() function 
 * to create an irregular sawtooth line.
 */
#include "Umfeld.h"

using namespace umfeld;

int   totalPts = 300;
float steps    = totalPts + 1;

void settings() {
    size(640, 360);
}

void setup() {
    stroke(1.f); //@diff(color_range)
    set_frame_rate(1.f);
}

void draw() {
    background(0.f);
    float rand = 0;
    for (int i = 1; i < steps; i++) {
        point((width / steps) * i, (height / 2) + random(-rand, rand));
        rand += random(-5, 5);
    }
}
