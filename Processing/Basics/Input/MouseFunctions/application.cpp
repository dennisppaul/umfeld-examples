/**
 * Mouse Functions. 
 * 
 * Click on the box and drag it across the screen. 
 */

#include "Umfeld.h"

using namespace umfeld;

float bx;
float by;
int   boxSize = 75;
bool  overBox = false; //@diff(generic_type)
bool  locked  = false; //@diff(generic_type)
float xOffset = 0.0;
float yOffset = 0.0;

void settings() {
    size(640, 360);
}

void setup() {
    bx = width / 2.0;
    by = height / 2.0;
    rectMode(RADIUS);
}

void draw() {
    background(0.f); //@diff(color_range)

    // Test if the cursor is over the box
    if (mouseX > bx - boxSize && mouseX < bx + boxSize &&
        mouseY > by - boxSize && mouseY < by + boxSize) {
        overBox = true;
        if (!locked) {
            stroke(1.f); //@diff(color_range)
            fill(0.6f); //@diff(color_range)
        }
    } else {
        stroke(0.6f); //@diff(color_range)
        fill(0.6f); //@diff(color_range)
        overBox = false;
    }

    // Draw the box
    rect(bx, by, boxSize, boxSize);
}

void mousePressed() {
    if (overBox) {
        locked = true;
        fill(1.f,1.f,1.f); //@diff(color_range)
    } else {
        locked = false;
    }
    xOffset = mouseX - bx;
    yOffset = mouseY - by;
}

void mouseDragged() {
    if (locked) {
        bx = mouseX - xOffset;
        by = mouseY - yOffset;
    }
}

void mouseReleased() {
    locked = false;
}