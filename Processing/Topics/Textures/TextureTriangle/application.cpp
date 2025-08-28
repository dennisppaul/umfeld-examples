/**
 * Texture Triangle. 
 * 
 * Using a rectangular image to map a texture onto a triangle.
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
    translate(width / 2, height / 2, 0);
    rotateY(map(mouseX, 0, width, -PI, PI));
    texture(img);
    beginShape(TRIANGLES);
    vertex(-100, -100, 0, 0.0f, 0.0f); // Top-left corner of texture (0,0)
    vertex(100, -40, 0, 1.0f, 0.3f); // Right side, slightly down (1, 0.3)
    vertex(0, 100, 0, 0.5f, 1.0f); // Bottom center (0.5, 1)
    endShape();
}
