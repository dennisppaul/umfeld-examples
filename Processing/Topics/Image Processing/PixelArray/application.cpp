/**
 * Pixel Array. 
 * 
 * Click and drag the mouse up and down to control the signal and 
 * press and hold any key to see the current pixel being read. 
 * This program sequentially reads the color of every pixel of an image
 * and displays this color to fill the window.  
 */
#include "Umfeld.h"

using namespace umfeld;

PImage* img;
int     direction = 1;
float   signal;

void settings() {
    size(640, 360);
}

void setup() {
    noFill();
    stroke(1.f); //@diff(color_range)
    set_frame_rate(30); //@diff(frameRate)
    img = loadImage("sea.jpg");
}

void draw() {
    if (signal > img->width * img->height - 1 || signal < 0) {
        direction = direction * -1;
    }

    if (isMousePressed) {
        int mx = constrain((int) mouseX, 0, (int) img->width - 1);
        int my = constrain((int) mouseY, 0, (int) img->height - 1);
        signal = my * img->width + mx;
    } else {
        signal += 0.33 * direction;
    }

    int sx = int(signal) % (int) img->width;
    int sy = int(signal) / (int) img->width;

    if (isKeyPressed) {
        loadPixels(img);
        point(sx, sy);
        rect(sx - 5, sy - 5, 10, 10);
    } else {
        uint32_t c = img->get(sx, sy);
        float r, g, b, a;
        color_unpack(c, r, g, b, a);
        background(r, g, b, a);
    }
}
