/**
 * Iteration. 
 * 
 * Iteration with a "for" structure to construct repetitive forms. 
 */

#include "Umfeld.h"

using namespace umfeld;


int y;
int num = 14;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.4f); //@diff(color_range)
    noStroke();
}

void draw() {
    // White bars
    fill(1.f); //@diff(color_range)
    y = 60;
    for (int i = 0; i < num / 3; i++) {
        rect(50, y, 475, 10);
        y += 20;
    }

    // Gray bars
    fill(0.2f); //@diff(color_range)
    y = 40;
    for (int i = 0; i < num; i++) {
        rect(405, y, 30, 10);
        y += 20;
    }
    y = 50;
    for (int i = 0; i < num; i++) {
        rect(425, y, 30, 10);
        y += 20;
    }

    // Thin lines
    y = 45;
    fill(0.f); //@diff(color_range)
    for (int i = 0; i < num - 1; i++) {
        rect(120, y, 40, 1);
        y += 20;
    }
}
