/**
 * Perspective vs. Ortho
 *
 * Move the mouse left to right to change the "far" 
 * parameter for the perspective() and ortho() functions.
 * This parameter sets the maximum distance from the 
 * origin away from the viewer and will clip the geometry.
 * Click a mouse button to switch between the perspective and
 * orthographic projections.
 */

#include "Umfeld.h" // @diff(include)

using namespace umfeld;

bool showPerspective = false;

void settings() {
    size(600, 360);
}

void setup() {
    noFill();
    fill(1.f); // when exeeding 1.f, shadow disappears in lighting, seems to need internal clamping? Do test with a big value like 10.f -- but unrelated to this example tho..

    noStroke();
    hint(ENABLE_DEPTH_TEST); // @diff(hints)
}

void draw() {
    background(0.f); // @diff(color_range)
    lights();
    float far = map(mouseX, 0, width, 120, 400);
    if (showPerspective == true) {
        perspective(PI / 3.0, float(width) / float(height), 10, far); // FIXME: disables the light completely
    } else {
        ortho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, 10, far); // FIXME: disables the light completely
    }
    translate(width / 2, height / 2, 0);
    rotateX(-PI / 6);
    rotateY(PI / 3);
    box(180);
    
    noLights();
}

void mousePressed() {
    showPerspective = !showPerspective;
}

/*
note:
- `pespective()` and `ortho()` disables the `lights()`.
*/

