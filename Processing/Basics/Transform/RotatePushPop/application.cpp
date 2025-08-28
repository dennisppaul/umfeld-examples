/**
 * Rotate Push Pop. 
 * 
 * The push() and pop() functions allow for more control over transformations.
 * The push function saves the current coordinate system to the stack 
 * and pop() restores the prior coordinate system. 
 */
#include "Umfeld.h"

using namespace umfeld;

float angle;                  // Angle of rotation
float offset = PI / 24.0; // Angle offset between boxes
int   num    = 12;        // Number of boxes

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE);
}

void setup() {
    hint(ENABLE_DEPTH_TEST); //@diff(available_hints)
    noStroke();
}

void draw() {

    lights();

    background(0.f, 0.f, .1f); //@diff(color_range)
    translate(width / 2, height / 2);

    for (int i = 0; i < num; i++) {
        float gray = map(i, 0, num - 1, 0, 1); //@diff(color_range)
        pushMatrix();
        fill(gray);
        rotateY(angle + offset * i);
        rotateX(angle / 2 + offset * i);
        box(200);
        popMatrix();
    }

    angle += 0.01;
}
