/**
 * Setup and Draw. 
 * 
 * The code inside the draw() function runs continuously
 * from top to bottom until the program is stopped. The
 * code in setup() is run once when the program starts.
 */

#include "Umfeld.h"

using namespace umfeld;

int y = 180;

void settings() {
    size(640, 360); // Size must be the first statement
}

// The statements in the setup() block run once
// when the program begins
void setup() {
    stroke(1.f); // Set line drawing color to white //@diff(color_range)
}

// The statements in draw() are run until the program
// is stopped. Each statement is run in sequence from top
// to bottom and after the last line is read, the
// first line is run again.
void draw() {
    background(0.f); // Clear the screen with a black background //@diff(color_range)
    line(0, y, width, y);
    y = y - 1;
    if (y < 0) {
        y = height;
    }
}
