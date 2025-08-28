/**
 * Bounce. 
 * 
 * When the shape hits the edge of the window, it reverses its direction. 
 */
#include "Umfeld.h"

using namespace umfeld;

int   rad = 60;   // Width of the shape
float xpos, ypos; // Starting position of shape

float xspeed = 2.8; // Speed of the shape
float yspeed = 2.2; // Speed of the shape

int xdirection = 1; // Left or Right
int ydirection = 1; // Top to Bottom

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    set_frame_rate(30); //@diff(frameRate)
    ellipseMode(RADIUS);
    // Set the starting position of the shape
    xpos = width / 2;
    ypos = height / 2;
}

void draw() {
    background(.4f); //@diff(color_range)

    // Update the position of the shape
    xpos = xpos + (xspeed * xdirection);
    ypos = ypos + (yspeed * ydirection);

    // Test to see if the shape exceeds the boundaries of the screen
    // If it does, reverse its direction by multiplying by -1
    if (xpos > width - rad || xpos < rad) {
        xdirection *= -1;
    }
    if (ypos > height - rad || ypos < rad) {
        ydirection *= -1;
    }

    // Draw the shape
    ellipse(xpos, ypos, rad, rad);
}
