/**
 * Get Child. 
 * 
 * SVG files can be made of many individual shapes. 
 * Each of these shapes (called a "child") has its own name 
 * that can be used to extract it from the "parent" file.
 * This example loads a map of the United States and creates
 * two new PShape objects by extracting the data from two states.
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    noFill();
    stroke(1.0f, 0.25f, 0.35f);
}

void draw() {
    background(0.85f);
    const float size = 50.0f;
    const float x    = width / 2.0f;
    const float y    = height / 2.0f;
    line(x - size, y - size, x + size, y + size);
    line(x - size, y + size, x + size, y - size);
}
