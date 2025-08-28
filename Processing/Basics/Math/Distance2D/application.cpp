/**
 * Distance 2D. 
 * 
 * Move the mouse across the image to obscure and reveal the matrix.  
 * Measures the distance from the mouse to each square and sets the
 * size proportionally. 
 */

#include "Umfeld.h"

using namespace umfeld;

float max_distance;

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    max_distance = dist(0.f, 0.f, width, height);
}

void draw() {
    background(0.f); //@diff(color_range)

    for (int i = 0; i <= width; i += 20) {
        for (int j = 0; j <= height; j += 20) {
            float size = dist(mouseX, mouseY, (float)i, (float)j); //@diff(argument_type)
            size       = size / max_distance * 66;
            ellipse(i, j, size, size);
        }
    }
}
