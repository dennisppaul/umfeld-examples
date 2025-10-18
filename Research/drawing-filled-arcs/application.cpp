/* this example shows how to draw in the 'setup()' function as well as in event functions ( e.g 'mousePressed()' ) */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(400, 400);
}

void setup() {
    //    colorMode(RGB, 1.0, 1.0, 1.0);
}

void draw() {
    background(0.5);

    stroke(0.0);
    fill(1.0);
    arc(50, 55, 50, 50, 0, HALF_PI);
    noFill();
    arc(50, 55, 60, 60, HALF_PI, PI);
    arc(50, 55, 70, 70, PI, PI + QUARTER_PI);
    arc(50, 55, 80, 80, PI + QUARTER_PI, TWO_PI);
}

