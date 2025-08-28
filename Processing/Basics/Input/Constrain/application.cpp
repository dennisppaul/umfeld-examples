/**
 * Constrain. 
 * 
 * Move the mouse across the screen to move the circle. 
 * The program constrains the circle to its box. 
 */
#include "Umfeld.h"

using namespace umfeld;

float mx;
float my;
float easing = 0.05;
int   radius = 24;
int   edge   = 100;
int   inner  = edge + radius;

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    ellipseMode(RADIUS);
    rectMode(CORNERS);
}

void draw() {
    background(.2f); //@diff(color_range)

    if (abs(mouseX - mx) > 0.1) {
        mx = mx + (mouseX - mx) * easing;
    }
    if (abs(mouseY - my) > 0.1) {
        my = my + (mouseY - my) * easing;
    }

    mx = constrain(mx, (float)inner, width - inner); // might need an override for the int
    my = constrain(my, (float)inner, height - inner);
    fill(.29f); //@diff(color_range)
    rect(edge, edge, width - edge, height - edge);
    fill(1.f); //@diff(color_range)
    ellipse(mx, my, radius, radius);
}