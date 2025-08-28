/**
 * Primitives 3D. 
 * 
 * Placing mathematically 3D objects in synthetic space.
 * The lights() method reveals their imagined dimension.
 * The box() and sphere() functions each have one parameter
 * which is used to specify their size. These shapes are
 * positioned using the translate() function.
 */
#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    background(0.f); //@diff(color_range)
    lights();
}

void draw() {
    noStroke();
    fill(1.f);
    pushMatrix();
    translate(130, height / 2, 0);
    rotateY(1.25);
    rotateX(-0.4);
    box(100);
    popMatrix();

    noFill();
    stroke(1.f); // needs clipping, if exceeding 1.f then whites out the light i.e shadow
    pushMatrix();
    translate(500, height * 0.35, -200);
    sphere(280);
    popMatrix();
}
/*
note:
- lights() does not work here
*/
