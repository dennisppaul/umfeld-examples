/**
 * Tile Images
 *
 * Draws an image larger than the screen, and saves the image as six tiles.
 * The scaleValue variable sets amount of scaling: 1 is 100%, 2 is 200%, etc.
 */

#include "Umfeld.h"

using namespace umfeld;

int scaleValue = 3; // Multiplication factor
int xoffset    = 0; // x-axis offset
int yoffset    = 0; // y-axis offset

void setOffset(); //@diff(forward_declaration)


void settings() {
    size(600, 600);
}

void setup() {
    stroke(0, .39f); //@diff(color_range)
}

void draw() {
    background(.8f); //@diff(color_range)
    scale(scaleValue);
    translate(xoffset * (-width / scaleValue), yoffset * (-height / scaleValue));
    line(10, 150, 500, 50);
    line(0, 600, 600, 0);
    saveFrame("lines-" + to_string(yoffset) + "-" + to_string(xoffset) + ".png"); //@diff(data_conversion)
    setOffset();
}

void setOffset() {
    xoffset++;
    if (xoffset == scaleValue) {
        xoffset = 0;
        yoffset++;
        if (yoffset == scaleValue) {
            println("Tiles saved.");
            exit();
        }
    }
}