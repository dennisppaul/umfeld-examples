/**
 * I Like Icosahedra
 * by Ira Greenberg.
 * 
 * This example plots icosahedra. The Icosahdron is a regular
 * polyhedron composed of twenty equalateral triangles.
 */
#include "Umfeld.h"
#include "Icosahedron.h"

using namespace umfeld;

Icosahedron ico1;
Icosahedron ico2;
Icosahedron ico3;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    hint(ENABLE_DEPTH_TEST); //@diff(avalable_hints)
    ico1 = Icosahedron(75);
    ico2 = Icosahedron(75);
    ico3 = Icosahedron(75);
}

void draw() {
    background(0.f); //@diff(color_range)
    lights(); // FIXME: the light disables the color of the shapes
    translate(width / 2, height / 2);

    pushMatrix();
    translate(-width / 3.5, 0);
    rotateX(frameCount * PI / 185);
    rotateY(frameCount * PI / -200);
    stroke(.66f, 0, 0); //@diff(color_range)
    noFill();
    ico1.create();
    popMatrix();

    pushMatrix();
    rotateX(frameCount * PI / 200);
    rotateY(frameCount * PI / 300);
    stroke(.58f, 0.f, .7f); //@diff(color_range)
    fill(.66f, .66f, 0.f); //@diff(color_range)
    ico2.create();
    popMatrix();

    pushMatrix();
    translate(width / 3.5, 0);
    rotateX(frameCount * PI / -200);
    rotateY(frameCount * PI / 200);
    noStroke();
    fill(0.f, 0.f, .72f); //@diff(color_range)
    ico3.create();
    popMatrix();
}
/*
note:
- the lights() turns the shapes color into grey
*/