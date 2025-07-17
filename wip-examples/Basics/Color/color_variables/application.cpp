#include "Umfeld.h"
#include <cstdint>

using namespace umfeld; // @diff(include)

// @diff(color_variable,color_range)
uint32_t inside  = color(0.8f, 0.4f, 0.f); 
uint32_t middle  = color(0.8f, 0.6f, 0.f);
uint32_t outside = color(0.6f, 0.2f, 0.f);

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    background(0.2f, 0, 0); // @diff(color_range)
}

void draw() {
    pushMatrix();
    translate(80, 80);
    fill_color(outside); // @diff(fill)
    rect(0, 0, 200, 200);
    fill_color(middle);
    rect(40, 60, 120, 120);
    fill_color(inside);
    rect(60, 90, 80, 80);
    popMatrix();

    pushMatrix();
    translate(360, 80);
    fill_color(inside);
    rect(0, 0, 200, 200);
    fill_color(outside);
    rect(40, 60, 120, 120);
    fill_color(middle);
    rect(60, 90, 80, 80);
    popMatrix();
}


