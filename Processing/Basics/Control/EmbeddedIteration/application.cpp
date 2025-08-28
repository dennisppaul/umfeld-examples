#include "Umfeld.h"

using namespace umfeld;

int gridSize = 40;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); // @diff(color_range)
}

void draw() {
    for (int x = gridSize; x <= width - gridSize; x += gridSize) {
        for (int y = gridSize; y <= height - gridSize; y += gridSize) {
            noStroke();
            fill(1.f); // @diff(color_range)
            rect(x - 1, y - 1, 3, 3);
            // alpha doesn't work somehow(umfeld)
            stroke(1.f, 0.4f); // @diff(color_range)
            line(x, y, width / 2, height / 2);
        }
    }
}
