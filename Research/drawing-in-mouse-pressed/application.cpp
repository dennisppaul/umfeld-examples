/* this example shows how to draw in the 'setup()' function as well as in event functions ( e.g 'mousePressed()' ) */

#include "Umfeld.h"

using namespace umfeld;

void arguments(const std::vector<std::string>& args) {
    for (const std::string& s: args) {
        console("  arg: ", s);
    }
}

void settings() {
    size(1024, 768);
}

void setup() {
    noFill();
    stroke(1.0f, 0.25f, 0.35f);
    background(0.85f);
    rectMode(CENTER);
    rect(width / 2, height / 2, 200, 200);
}

void draw() {
    // background(0.85f);
    stroke(1.0, 0.0, 0.0);
    line(width, height, mouseX, mouseY);
}

void mouseMoved() {
    stroke(0.0, 0.0, 1.0);
    line(0, 0, mouseX, mouseY);
}
