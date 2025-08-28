/**
 * Spot. 
 * 
 * Move the mouse the change the position and concentation
 * of a blue spot light. 
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    noStroke();
    fill(.8f); //@diff(color_range)
    sphereDetail(60);
}

void draw() {
    background(0.f); //@diff(color_range)

    // Light the bottom of the sphere
    // directionalLight(51, 102, 126, 0, -1, 0); //FIXME: error: ‘directionalLight’ was not declared in this scope

    // Orange light on the upper-right of the sphere
    // spotLight(204, 153, 0, 360, 160.f, 600, 0, 0, -1, PI / 2, 600); //FIXME: error: ‘spotLight’ was not declared in this scope

    // Moving spotlight that follows the mouse
    // spotLight(102, 153, 204, 360, mouseY, 600, 0, 0, -1, PI / 2, 600); //FIXME: error: ‘spotLight’ was not declared in this scope

    translate(width / 2, height / 2, 0);
    sphere(120);
}
