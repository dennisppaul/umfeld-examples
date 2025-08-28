/**
 * Redraw. 
 * 
 * The redraw() function makes draw() execute once.  
 * In this example, draw() is executed once every time 
 * the mouse is clicked. 
 */
#include "Umfeld.h"

using namespace umfeld;

float y;

void settings() {
size(640, 360); // Size should be the first statement
}

// The statements in the setup() function
// execute once when the program begins
void setup() {
    stroke(1.f);    // Set line drawing color to white //@diff(color_range)
    noLoop();
    y = height * 0.5;
}

// The code in draw() is run until the program
// is stopped. Each statement is executed in
// sequence and after the last line is read,
// the first line is run again.
void draw() {
    background(0.f); // Set the background to black //@diff(color_range)
    y = y - 4;
    if (y < 0) { y = height; }
    line(0, y, width, y);
}

void mousePressed() {
    redraw();
}
/*
note:
- FIXME
- redraw behaves different than in processing.
- processing::redraw() runs the draw() for one frame,
- but umfeld::redraw() disables the noLoop() and enables the loop again.
*/