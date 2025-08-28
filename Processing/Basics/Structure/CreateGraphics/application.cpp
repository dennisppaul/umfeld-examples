/**
 * Create Graphics. 
 * 
 * The createGraphics() function creates an object from 
 * the PGraphics class. PGraphics is the main graphics and 
 * rendering context for Processing. The beginDraw() method 
 * is necessary to prepare for drawing and endDraw() is
 * necessary to finish. Use this class if you need to draw 
 * into an off-screen graphics buffer or to maintain two 
 * drawing surfaces with different properties.
 */

#include "Umfeld.h"

using namespace umfeld;

PGraphics* pg; //@diff(pointer)

void settings() {
    size(640, 360);
}

void setup() {
    pg = createGraphics(400, 200);
}

void draw() {
    fill(0.f, 0.04f); //@diff(color_range)
    rect(0, 0, width, height);
    fill(1.f); //@diff(color_range)
    noStroke();
    ellipse(mouseX, mouseY, 60, 60);

    pg->beginDraw(); //@diff(pointer)
    pg->background(.2f); //@diff(pointer,color_range)
    pg->noFill(); //@diff(pointer)
    pg->stroke(1.f); //@diff(pointer,color_range)
    pg->ellipse(mouseX - 120, mouseY - 60, 60, 60); //@diff(pointer)
    pg->endDraw(); //@diff(pointer)

    // Draw the offscreen buffer to the screen with image()
    image(pg, 120, 60);
}
