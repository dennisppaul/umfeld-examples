/**
 * Width and Height. 
 * 
 * The 'width' and 'height' variables contain the width and height 
 * of the display window as defined in the size() function. 
 */
#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
}

void draw() {
    background(.5f); //@diff(color_range)
    noStroke();
    for (int i = 0; i < height; i += 20) {
        fill(.5f, .8f, .05f); //@diff(color_range)
        rect(0, i, width, 10);
        fill(1.f); //@diff(color_range)
        rect(i, 0, 10, height);
    }
}
