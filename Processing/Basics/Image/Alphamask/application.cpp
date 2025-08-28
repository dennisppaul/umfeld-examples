/**
 * Alpha Mask. 
 * 
 * Loads a "mask" for an image to specify the transparency 
 * in different parts of the image. The two images are blended
 * together using the mask() method of PImage. 
 */
#include "Umfeld.h"

using namespace umfeld;

PImage* img; //@diff(pointer)
PImage* imgMask; //@diff(pointer)

void settings() {
    size(640, 360);
}

void setup() {
    img     = loadImage("moonwalk.jpg");
    imgMask = loadImage("mask.jpg");
    // img->mask(imgMask); //unimplemented
	rectMode(CENTER);
    // imageMode(CENTER); //unimplemented
    
}

void draw() {
    background(0, 0.4f, 0.6f); //@diff(color_range)

    image(img, width/2, height/2);
    image(img, mouseX, mouseY);
}
