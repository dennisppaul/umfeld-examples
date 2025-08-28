/**
 * Save One Image
 * 
 * The save() function allows you to save an image from the 
 * display window. In this example, save() is run when a mouse
 * button is pressed. The image "line.tif" is saved to the 
 * same folder as the sketch's program file.
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
}

void draw() {
    background(.8f); //@diff(color_range)
    line(0, 0, mouseX, height);
    line(width, 0, 0, mouseY);
}

void mousePressed() {
    // saveFrame("line.tif"); // *.tif is unsupported
    saveFrame("line.png"); // Save as PNG instead
}
/*
note:
- .tif is unimplemented though I don't think it is needed
*/