/**
 * Move Eye. 
 * by Simon Greenwold.
 * 
 * The camera lifts up (controlled by mouseY) while looking at the same point.
 */


#include "Umfeld.h" // @diff(include)

using namespace umfeld;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); // @diff(renderer)
}

void setup() {
    fill(0.8f);
    hint(ENABLE_DEPTH_TEST); // @note(available_hints)
}

void draw() {
    lights();
    background(.0); // @diff(color_range)

    // Change height of the camera with mouseY
    camera(30.0, mouseY, 220.0, // eyeX, eyeY, eyeZ
           0.0, 0.0, 0.0,       // centerX, centerY, centerZ
           0.0, 1.0, 0.0);      // upX, upY, upZ

    noStroke();
    box(90);
    stroke(1.f); // @diff(color_range)
    line(-100, 0, 0, 100, 0, 0);
    line(0, -100, 0, 0, 100, 0);
    line(0, 0, -100, 0, 0, 100);

    noLights();
}
