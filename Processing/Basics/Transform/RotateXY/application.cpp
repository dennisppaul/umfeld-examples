/**
 * Rotate 1. 
 * 
 * Rotating simultaneously in the X and Y axis. 
 * Transformation functions such as rotate() are additive.
 * Successively calling rotate(1.0) and rotate(2.0)
 * is equivalent to calling rotate(3.0). 
 */

#include "Umfeld.h"

using namespace umfeld;

float angle = 0.0;
float rSize; // rectangle size

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE);  //@diff(renderer)
}

void setup() {
    hint(ENABLE_DEPTH_TEST); //@diff(available_hints)
    rSize = width / 6;
    noStroke();
    fill(.8f, .8f); //@diff(color_range)
}

void draw() {
    background(.5f); //@diff(color_range)

    angle += 0.005;
    if (angle > TWO_PI) {
        angle = 0.0;
    }

    translate(width / 2, height / 2);

    rotateX(angle);
    rotateY(angle * 2.0);
    fill(1.f); //@diff(color_range)
    rect(-rSize, -rSize, rSize * 2, rSize * 2);

    rotateX(angle * 1.001);
    rotateY(angle * 2.002);
    fill(0.f); //@diff(color_range)
    rect(-rSize, -rSize, rSize * 2, rSize * 2);
}
