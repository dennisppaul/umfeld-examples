/**
 * Load and Display 
 * 
 * Images can be loaded and displayed to the screen at their actual size
 * or any other size. 
 */

#include "Umfeld.h"

using namespace umfeld;

PImage* img; // Declare variable "img" of type PImage //@diff(pointer)

void settings() {
    size(640, 360);
}

void setup() {
    // The image file must be in the data folder of the current sketch
    // to load successfully
    img = loadImage("moonwalk.jpg"); // Load the image into the program
}

void draw() {
    // Displays the image at its actual size at point (0,0)
    image(img, 0, 0);
    // Displays the image at point (0, height/2) at half of its size
    image(img, 0, height / 2, img->width / 2, img->height / 2); //@diff(pointer)
}
