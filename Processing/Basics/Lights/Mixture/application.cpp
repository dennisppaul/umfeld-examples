/**
 * Mixture
 * by Simon Greenwold. 
 * 
 * Display a box with three different kinds of lights. 
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    noStroke();
}

void draw() {
    background(0.f); //@diff(color_range)
    translate(width / 2, height / 2);

    // FIXME: error: ‘pointLight’ was not declared in this scope
    // Orange point light on the right
    // pointLight(150, 100, 0,   // Color
    //           200, -150, 0); // Position
    
    // FIXME: error: 'directionalLight' was not declared in this scope
    // Blue directional light from the left
    // directionalLight(0, 102, 255, // Color
    //                  1, 0, 0);    // The x-, y-, z-axis direction

    // FIXME: error: ‘spotLight’ was not declared in this scope
    // spotLight(255, 255, 109, // Color
    //          0, 40, 200,    // Position
    //          0, -0.5, -0.5, // Direction
    //          PI / 2, 2);    // Angle, concentration

    rotateY(map(mouseX, 0, width, 0, PI));
    rotateX(map(mouseY, 0, height, 0, PI));
    box(150);
}