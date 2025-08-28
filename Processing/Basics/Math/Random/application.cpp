/**
 * Random. 
 * 
 * Random numbers create the basis of this image. 
 * Each time the program is loaded the result is different. 
 */
#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
    strokeWeight(20);
    set_frame_rate(2); //@diff(frameRate)
}

void draw() {
    for (int i = 0; i < width; i++) {
        float r = random(0.f, 1.f); 
        stroke(r); //@diff(color_range)
        line(i, 0, i, height);
    }
}
