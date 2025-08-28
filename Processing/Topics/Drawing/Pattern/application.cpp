/**
 * Patterns. 
 * 
 * Move the cursor over the image to draw with a software tool 
 * which responds to the speed of the mouse. 
 */
#include "Umfeld.h"

using namespace umfeld;

static int lastMouseX = 0; //DEBUG
static int lastMouseY = 0; //DEBUG

void variableEllipse(int x, int y, int px, int py); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    background(.4f); //@diff(color_range)
    lastMouseX = mouseX; //DEBUG
    lastMouseY = mouseY; //DEBUG
}

void draw() {
    // Call the variableEllipse() method and send it the
    // parameters for the current mouse position
    // and the previous mouse position
    variableEllipse(mouseX, mouseY, lastMouseX, lastMouseY);
    lastMouseX = mouseX; //DEBUG
    lastMouseY = mouseY; //DEBUG
}


// The simple method variableEllipse() was created specifically
// for this program. It calculates the speed of the mouse
// and draws a small ellipse if the mouse is moving slowly
// and draws a large ellipse if the mouse is moving quickly

void variableEllipse(int x, int y, int px, int py) {
    float speed = abs(x - px) + abs(y - py);
    stroke(speed / 255.f); //@diff(color_range)
    ellipse(x, y, speed, speed);
}
/*
note: same issue as the continuous_lines example,
        see the note in the continuous_lines/application.cpp file
*/