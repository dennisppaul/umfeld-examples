/**
 * Color Variables (Homage to Albers). 
 * 
 * This example creates variables for colors that may be referred to 
 * in the program by a name, rather than a number. 
 */

#include "Umfeld.h"

using namespace umfeld;

uint32_t inside  = color(0.8f, 0.4f, 0); //@diff(color_range, color_type)
uint32_t middle  = color(0.8f, 0.6f, 0); //@diff(color_range, color_type)
uint32_t outside = color(0.6f, 0.2f, 0); //@diff(color_range, color_type)

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    background(0.2f, 0, 0); //@diff(color_range);
}

void draw() {
    pushMatrix();
    translate(80, 80);
    fill_color(outside); //@diff(fill_color)
    rect(0, 0, 200, 200);
    fill_color(middle); //@diff(fill_color)
    rect(40, 60, 120, 120);
    fill_color(inside); //@diff(fill_color)
    rect(60, 90, 80, 80);
    popMatrix();

    pushMatrix();
    translate(360, 80);
    fill_color(inside); //@diff(fill_color)
    rect(0, 0, 200, 200);
    fill_color(outside); //@diff(fill_color)
    rect(40, 60, 120, 120);
    fill_color(middle); //@diff(fill_color)
    rect(60, 90, 80, 80);
    popMatrix();
}
