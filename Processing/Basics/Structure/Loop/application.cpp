/**
 * Loop. 
 * 
 * If noLoop() is run in setup(), the code in draw() 
 * is only run once. In this example, click the mouse 
 * to run the loop() function to cause the draw() the 
 * run continuously. 
 */
#include "Umfeld.h"

using namespace umfeld;

float y = 180;

void settings() {
    size(640, 360); // Size should be the first statement
}

// The statements in the setup() function
// run once when the program begins
void setup() {
    stroke(1.f);    // Set stroke color to white //@diff(color_range)
    noLoop();
}

void draw() {
    background(0.f); // Set the background to black //@diff(color_range)
    line(0, y, width, y);
    y = y - 1;
    if (y < 0) {
        y = height;
    }
}

void mousePressed() {
    // loop(); // unimplemented
    redraw(); 
}
/*
note:
- redraw() behaves like loop() in this context
*/