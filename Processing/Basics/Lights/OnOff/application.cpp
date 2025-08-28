/**
 * On/Off.  
 * 
 * Uses the default lights to show a simple box. The lights() function
 * is used to turn on the default lighting. Click the mouse to turn the
 * lights off.
 */

#include "Umfeld.h"

using namespace umfeld;

float spin = 0.0;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
    
}

void setup() {
    hint(ENABLE_DEPTH_TEST); //@diff(available_hints)
    noStroke();
}

void draw() {
    background(.2f); //@diff(color_range)

    if (!isMousePressed) {
        lights();
    }

    spin += 0.01;

    pushMatrix();
    translate(width / 2, height / 2, 0);
    rotateX(PI / 9);
    rotateY(PI / 5 + spin);
    box(150);
    popMatrix();
}
