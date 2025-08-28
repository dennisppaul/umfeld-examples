/**
 * Mouse 2D. 
 * 
 * Moving the mouse changes the position and size of each box. 
 */
#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    rectMode(CENTER);
}

void draw() {
    background(.2f);
    fill(1.f, .8f);
    rect(mouseX, height / 2, mouseY / 2 + 10, mouseY / 2 + 10);
    fill(1.f, .8f);
    int inverseX = width - mouseX;
    int inverseY = height - mouseY;
    rect(inverseX, height / 2, (inverseY / 2) + 10, (inverseY / 2) + 10);
}
