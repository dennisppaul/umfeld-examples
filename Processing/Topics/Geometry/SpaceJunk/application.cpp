/**
 * Space Junk  
 * by Ira Greenberg (zoom suggestion by Danny Greenberg).
 * 
 * Rotating cubes in space using a custom Cube class. 
 * Color controlled by light sources. Move the mouse left
 * and right to zoom.
 */
#include "Umfeld.h"
#include "Cube.h"

using namespace umfeld;

// Used for oveall rotation
float angle;

// Cube count-lower/raise to test performance
int limit = 500;

// Array for all cubes
std::vector<Cube> cubes(limit);

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    background(0.f); //@diff(color_range)
    noStroke();

    // Instantiate cubes, passing in random vals for size and postion
    for (int i = 0; i < cubes.size(); i++) {
        cubes[i] = Cube(int(random(-10, 10)), int(random(-10, 10)),
                        int(random(-10, 10)), int(random(-140, 140)),
                        int(random(-140, 140)), int(random(-140, 140)));
    }
}

void draw() {
    background(0.f); //@diff(color_range)
    fill(.78f); //@diff(color_range)

    // Set up some different colored lights
    // pointLight(51, 102, 255, 65, 60, 100); //unimplemented
    // pointLight(200, 40, 60, -65, -60, -150);

    // Raise overall light in scene
    // ambientLight(70, 70, 10); //unimplemented

    // Center geometry in display windwow.
    // you can changlee 3rd argument ('0')
    // to move block group closer(+) / further(-)
    translate(width / 2, height / 2, -200 + mouseX * 0.65);

    // Rotate around y and x axes
    rotateY(radians(angle));
    rotateX(radians(angle));

    // Draw cubes
    for (int i = 0; i < cubes.size(); i++) {
        cubes[i].drawCube();
    }

    // Used in rotate function calls above
    angle += 0.2;
}
