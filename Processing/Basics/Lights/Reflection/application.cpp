/**
 * Reflection 
 * by Simon Greenwold. 
 * 
 * Vary the specular reflection component of a material
 * with the horizontal position of the mouse. 
 */


#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    noStroke();
    fill(0.4f); //@diff(color_range)
}

void draw() {
    background(0.f); //@diff(color_range)
    translate(width / 2, height / 2);
    // Set the specular color of lights that follow
    // lightSpecular(1, 1, 1); //FIXME: error: ‘lightSpecular’ was not declared in this scope
    // directionalLight(0.8, 0.8, 0.8, 0, 0, -1); //FIXME: error: ‘directionalLight’ was not declared in this scope
    float s = mouseX / float(width);
    // specular(s, s, s); //FIXME: error: ‘specular’ was not declared in this scope
    sphere(120);
}
