/**
 * Scale 
 * by Denis Grutze. 
 * 
 * Paramenters for the scale() function are values specified 
 * as decimal percentages. For example, the method call scale(2.0) 
 * will increase the dimension of the shape by 200 percent. 
 * Objects always scale from the origin. 
 */

#include "Umfeld.h"

using namespace umfeld;

float angle = 0.0;
float s = 0.0;


void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    rectMode(CENTER);
    set_frame_rate(30); //@diff(frameRate)
}

void draw() {

    background(.4f); //@diff(color_range)

    angle = angle + 0.04;
    s = cos(angle) * 2;

    translate(width / 2, height / 2);
    scale(s);
    fill(.2f); //@diff(color_range)
    rect(0, 0, 50, 50);

    translate(75, 0);
    fill(1.f); //@diff(color_range)
    scale(s);
    rect(0, 0, 50, 50);
}
