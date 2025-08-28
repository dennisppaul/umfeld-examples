/**
 * Loading Images. 
 * 
 * Umfeld applications can load images from the network. 
 */
#include "Umfeld.h"

using namespace umfeld;

PImage* img; //@diff(pointer)

void settings() {
    size(640, 360);
}

void setup() {
    img = loadImage("https://github.com/dennisppaul/umfeld-examples/blob/main/Advanced/texture-filtering/data/umfeld-logotype-64.png?raw=true"); //@diff(pointer)
    noLoop();
}

void draw() {
    background(0.f);      //@diff(color_range)
    if (img != nullptr) { //@diff(pointer)
        for (int i = 0; i < 5; i++) {
            image(img, 0, img->height * i); //@diff(pointer)
        }
    }
}
