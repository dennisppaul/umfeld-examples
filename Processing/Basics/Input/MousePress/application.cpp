/**
 * Mouse Press. 
 * 
 * Move the mouse to position the shape. 
 * Press the mouse button to invert the color. 
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    hint(DISABLE_SMOOTH_LINES); //@diff(available_hints)
    fill(.5f);                  //@diff(color_range)
    background(.4f);            //@diff(color_range)
}

void draw() {
    if (isMousePressed) {
        stroke(1.f); //@diff(color_range)
    } else {
        stroke(0.f); //@diff(color_range)
    }
    line(mouseX - 66, mouseY, mouseX + 66, mouseY);
    line(mouseX, mouseY - 66, mouseX, mouseY + 66);
}
