/**
 * Linear Image. 
 * 
 * Click and drag mouse up and down to control the signal. 
 * Press and hold any key to watch the scanning. 
 */

#include "Umfeld.h"
#include <algorithm>

using namespace umfeld;

PImage* img;
int    direction = 1;

float signal;

void settings() {
    size(640, 360);
}

void setup() {
    stroke(1.f); //@diff(color_range)
    img = loadImage("sea.jpg");
    img->loadPixels(g);
    loadPixels();
}

void draw() {
    if (signal > img->height - 1 || signal < 0) {
        direction = direction * -1;
    }
    if (isMousePressed == true) {
        signal = abs((int)mouseY % int(img->height));
    } else {
        signal += (0.3 * direction);
    }

    if (isKeyPressed == true) {
        img->loadPixels(g);
        line(0, signal, img->width, signal);
    } else {
        int signalOffset = int(signal) * img->width;
        for (int y = 0; y < img->height; y++) {
            std::copy(img->pixels + signalOffset, 
                     img->pixels + signalOffset + static_cast<int>(img->width), 
                     pixels + y * static_cast<int>(width));
        }
        updatePixels();
    }
}
