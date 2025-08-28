/**
 * Sine Cosine. 
 * 
 * Linear movement with sin() and cos(). 
 * Numbers between 0 and PI*2 (TWO_PI which angles roughly 6.28) 
 * are put into these functions and numbers between -1 and 1 are 
 * returned. These values are then scaled to produce larger movements. 
 */
#include "Umfeld.h"

using namespace umfeld;


float xx1, xx2, yy1, yy2;
float angle1, angle2;
float scalar = 70;

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    rectMode(CENTER);
}

void draw() {
    background(0.f); //@diff(color_range)

    float ang1 = radians(angle1);
    float ang2 = radians(angle2);

    xx1 = width / 2 + (scalar * cos(ang1));
    xx2 = width / 2 + (scalar * cos(ang2));

    yy1 = height / 2 + (scalar * sin(ang1));
    yy2 = height / 2 + (scalar * sin(ang2));

    fill(1.f); //@diff(color_range)
    rect(width * 0.5, height * 0.5, 140, 140);

    fill(0.f, .4f, .6f); //@diff(color_range)
    ellipse(xx1, height * 0.5 - 120, scalar, scalar);
    ellipse(xx2, height * 0.5 + 120, scalar, scalar);

    fill(1.f, .8f, 0.f); //@diff(color_range)
    ellipse(width * 0.5 - 120, yy1, scalar, scalar);
    ellipse(width * 0.5 + 120, yy2, scalar, scalar);

    angle1 += 2;
    angle2 += 3;
}
