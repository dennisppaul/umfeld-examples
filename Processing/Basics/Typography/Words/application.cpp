/**
 * Words. 
 * 
 * The text() function is used for writing words to the screen.
 * The letters can be aligned left, center, or right with the 
 * textAlign() function. 
 */

#include "Umfeld.h"

using namespace umfeld;

PFont* f; //@diff(pointer)

void drawType(float x);

void settings() {
        size(640, 360);
}

void setup() {
    // Create the font
    //   printArray(PFont.list()); //unimplemented
    // f = createFont("SpaceMono-Regular.ttf", 18); //unimplemented
    f = loadFont("SpaceMono-Regular.ttf", 18); //@diff(loadFont)
    textFont(f);
}

void draw() {
    background(.4f); //@diff(color_range)
    textAlign(RIGHT);
    drawType(width * 0.25);
    textAlign(CENTER);
    drawType(width * 0.5);
    textAlign(LEFT);
    drawType(width * 0.75);
}

void drawType(float x) {
    line(x, 0, x, 65);
    line(x, 220, x, height);
    fill(0.f); //@diff(color_range)
    text("ichi", x, 95);
    fill(.2f); //@diff(color_range)
    text("ni", x, 130);
    fill(.8f); //@diff(color_range)
    text("san", x, 165);
    fill(1.f); //@diff(color_range)
    text("shi", x, 210);
}
