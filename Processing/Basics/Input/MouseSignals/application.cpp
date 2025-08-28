/**
 * Mouse Signals 
 * 
 * Move and click the mouse to generate signals. 
 * The top row is the signal from "mouseX", 
 * the middle row is the signal from "mouseY",
 * and the bottom row is the signal from "mousePressed". 
 */

#include "Umfeld.h"

using namespace umfeld;

std::vector<int> xvals; //@diff(std::vector)
std::vector<int> yvals; //@diff(std::vector)
std::vector<int> bvals; //@diff(std::vector)

void settings() {
    size(640, 360);
}

void setup() {
    hint(DISABLE_SMOOTH_LINES); //@diff(available_hints)
    xvals.resize(width);        //@diff(std::vector)
    yvals.resize(width);        //@diff(std::vector)
    bvals.resize(width);        //@diff(std::vector)
}

void draw() {
    background(.4f); //@diff(color_range)

    for (int i = 1; i < width; i++) {
        xvals[i - 1] = xvals[i];
        yvals[i - 1] = yvals[i];
        bvals[i - 1] = bvals[i];
    }
    // Add the new values to the end of the array
    xvals[width - 1] = mouseX;
    yvals[width - 1] = mouseY;

    if (isMousePressed == true) { //@diff(mouse_pressed)
        bvals[width - 1] = 0;
    } else {
        bvals[width - 1] = height / 3;
    }

    fill(1.f); //@diff(color_range)
    noStroke();
    rect(0, height / 3, width, height / 3 + 1);

    for (int i = 1; i < width; i++) {
        // Draw the x-values
        stroke(1.f); //@diff(color_range)
        point(i, map(xvals[i], 0, width, 0, height / 3 - 1)); //FIXME: does not draw anything.

        // Draw the y-values
        stroke(0.f); //@diff(color_range)
        point(i, height / 3 + yvals[i] / 3); //FIXME: does not draw anything.

        // Draw the mouse presses
        stroke(1.f); //@diff(color_range)
        line(i, (2 * height / 3) + bvals[i], i, (2 * height / 3) + bvals[i - 1]);
    }
}
