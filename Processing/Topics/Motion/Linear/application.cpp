/**
 * Linear Motion. 
 * 
 * Changing a variable to create a moving line.  
 * When the line moves off the edge of the window, 
 * the variable is set to 0, which places the line
 * back at the bottom of the screen. 
 */
#include "Umfeld.h"

using namespace umfeld;

float aa;

void settings() {
    size(640, 360);
}

void setup() {
    stroke(1.f); //@diff(color_range)
    aa = height / 2;
}

void draw() {
    background(.2f); //@diff(color_range)
    line(0, aa, width, aa);
    aa = aa - 0.5;
    if (aa < 0) {
        aa = height;
    }
}
