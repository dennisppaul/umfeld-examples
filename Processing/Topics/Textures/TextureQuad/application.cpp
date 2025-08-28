/**
 * Texture Quad. 
 * 
 * Load an image and draw it onto a quad. The texture() function sets
 * the texture image. The vertex() function maps the image to the geometry.
 */
#include "Umfeld.h"

using namespace umfeld;

PImage* img;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    img = loadImage("berlin-1.jpg");
    noStroke();
}

void draw() {
    background(0.f); //@diff(color_range)
    translate(width / 2, height / 2);
    rotateY(map(mouseX, 0, width, -PI, PI));
    rotateZ(PI / 6);
    texture(img);
    beginShape();
    vertex(-100, -100, 0, 0, 0);
    vertex(100, -100, 0, 1, 0); //@diff(texture_coords): normalized texture coordinates (0-1)
    vertex(100, 100, 0, 1, 1); //@diff(texture_coords): normalized texture coordinates (0-1)
    vertex(-100, 100, 0, 0, 1); //@diff(texture_coords): normalized texture coordinates (0-1)
    endShape();
}
/*
note:
- texture coordinates must be normalized to the range [0, 1]
*/