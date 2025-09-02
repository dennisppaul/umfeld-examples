// TODO WIP there are still a lot of things very broken here …

/*
 * this example shows how to use the camera
 * from https://processing.org/reference/camera_.html
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(1024, 768, P3D);
}

void setup() {
    strokeWeight(3);
    rectMode(CENTER);
}

void draw() {
    background(0.85f);

    fill(0);
    debug_text("FPS   : " + nf(frameRate, 1), 10, 10);

    camera();

    noFill();
    stroke(0.0f);
    translate(width / 2, height / 2, 0);
    rotateX(frameCount * 0.01f);
    rotateY(frameCount * 0.0037f);
    square(0, 0, 200);

    constexpr float fov            = DEFAULT_CAMERA_FOV_RADIANS;
    const float     cameraDistance = (height / 2.0f) / tan(fov / 2.0f);
    camera(width / 2.0, height / 2.0 - 200, cameraDistance,
           mouseX, mouseY, 0,
           0, 1, 0);

    fill(1, 0.25, 0.35);
    stroke(0);
    for (int x = -20; x < 20; ++x) {
        for (int y = -20; y < 20; ++y) {
            pushMatrix();
            translate(x * 60, 0, y * 60);
            box(20);
            popMatrix();
        }
    }
}
