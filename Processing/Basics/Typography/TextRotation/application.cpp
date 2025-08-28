/**
 * Text Rotation. 
 * 
 * Draws letters to the screen and rotates them at different angles.
 */
#include "Umfeld.h"

using namespace umfeld;

PFont* f; //@diff(pointer)
float angleRotate = 0.0;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)

    // Create the font from the .ttf file in the data folder
    // f = createFont("SourceCodePro-Regular.ttf", 18); //unimplemented
    f = loadFont("SourceCodePro-Regular.ttf", 18); //@diff(loadFont)
    textFont(f);
}

void draw() {
    background(0.f); //@diff(color_range)

    strokeWeight(1.f);
    stroke(.6f); //@diff(color_range)

    pushMatrix();
    float angle1 = radians(45);
    translate(100, 180);
    rotate(angle1);
    text("45 DEGREES", 0, 0);
    line(0, 0, 150, 0);
    popMatrix();

    pushMatrix();
    float angle2 = radians(270);
    translate(200, 180);
    rotate(angle2);
    text("270 DEGREES", 0, 0);
    line(0, 0, 150, 0);
    popMatrix();

    pushMatrix();
    translate(440, 180);
    rotate(radians(angleRotate));
    text(to_string(int(angleRotate) % 360, " DEGREES"), 0, 0); //@diff(text)
    line(0, 0, 150, 0);
    popMatrix();

    angleRotate += 0.25;

    stroke(1.f, 0.f, 0.f); //@diff(color_range)
    strokeWeight(4);
    point(100, 180);
    point(200, 180);
    point(440, 180);
}
/*
note:
= the text() is drawing the bounding box of the text.
- compare the text() after calling noStroke()
*/