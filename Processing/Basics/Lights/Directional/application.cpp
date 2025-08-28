/**
 * Directional. 
 * 
 * Move the mouse the change the direction of the light.
 * Directional light comes from one direction and is stronger 
 * when hitting a surface squarely and weaker if it hits at a 
 * a gentle angle. After hitting a surface, a directional lights 
 * scatters in all directions. 
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE);
}

void setup() {
    noStroke();
    fill(.8f); //@diff(color_range)
}

void draw() {
    noStroke();
    background(0.f); //@diff(color_range)
    float dirY = (mouseY / float(height) - 0.5) * 2;
    float dirX = (mouseX / float(width) - 0.5) * 2;
//    directionalLight(.8f, .8f, .8f, -dirX, -dirY, -1.f); //FIXME: error: ‘directionalLight’ was not declared in this scope 
    translate(width / 2 - 100, height / 2, 0);
    sphere(80);
    translate(200, 0, 0);
    sphere(80);
}
