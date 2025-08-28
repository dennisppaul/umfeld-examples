/**
 * Texture Cylinder. 
 * 
 * Load an image and draw it onto a cylinder and a quad. 
 */

#include "Umfeld.h"

using namespace umfeld;

int tubeRes = 32;
std::vector<float> tubeX(tubeRes);
std::vector<float> tubeY(tubeRes);
PImage* img;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE);
}

void setup() {
    img = loadImage("berlin-1.jpg");
    float angle = 270.0 / tubeRes;
    for (int i = 0; i < tubeRes; i++) {
        tubeX[i] = cos(radians(i * angle));
        tubeY[i] = sin(radians(i * angle));
    }
    noStroke();
    hint(ENABLE_DEPTH_TEST);
}

void draw() {
    background(0.f); //@diff(color_range)
    translate(width / 2, height / 2);
    rotateX(map(mouseY, 0, height, -PI, PI));
    rotateY(map(mouseX, 0, width, -PI, PI));
    texture(img);
    beginShape(QUAD_STRIP);
    for (int i = 0; i < tubeRes; i++) {
        float x = tubeX[i] * 100;
        float z = tubeY[i] * 100;
        float u = img->width / tubeRes * i;
        vertex(x, -100, z, u, 0);
        vertex(x, 100, z, u, img->height);
    }
    endShape();
    
    texture(img);
    beginShape(QUADS);
    vertex(0, -100, 0, 0, 0);
    vertex(100, -100, 0, 100, 0);
    vertex(100, 100, 0, 100, 100);
    vertex(0, 100, 0, 0, 100);
    endShape();
}
