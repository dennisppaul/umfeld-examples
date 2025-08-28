/**
 * Request Image
 * by Ira Greenberg 
 * 
 * Shows how to use the requestImage() function with preloader animation. 
 * The requestImage() function loads images on a separate thread so that 
 * the sketch does not freeze while they load. It's useful when you are 
 * loading large images. These images are small for a quick download, but 
 * try it with your own huge images to get the full effect. 
 */
#include "Umfeld.h"

using namespace umfeld;


int imgCount  = 12;
std::vector<PImage*> imgs(imgCount); //@diff(std::vector)
float imgW;

// Keeps track of loaded images (true or false)
std::vector<bool> loadStates(imgCount); //@diff(std::vector)

// For loading animation
float loaderX, loaderY, theta;

void drawImages(); //@diff(forward_declaration
void runLoaderAni(); //@diff(forward_declaration
bool checkLoadStates(); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    imgW = width / imgCount;

    // Load images asynchronously
    // for (int i = 0; i < imgCount; i++) {
    //     imgs[i] = requestImage("PT_anim" + nf(i, 4) + ".gif"); // unimplemented
    // }
}

void draw() {
    background(0.f); //@diff(color_range)

    // Start loading animation
    runLoaderAni();

    // for (int i = 0; i < imgs.size(); i++) { //@diff(std::vector)
    //     // Check if individual images are fully loaded
    //     if ((imgs[i]->width != 0) && (imgs[i]->width != -1)) { //@diff(pointer)
    //         // As images are loaded set true in boolean array
    //         loadStates[i] = true;
    //     }
    // }
    // When all images are loaded draw them to the screen
    if (checkLoadStates()) {
        drawImages();
    }
}

void drawImages() {
    // int y = (height - imgs[0]->height) / 2;
    // for (int i = 0; i < imgs.size(); i++) { //@diff(std::vector)
    //     image(imgs[i], width / imgs.size() * i, y, imgs[i]->height, imgs[i]->height); //@diff(pointer)
    // }
}

// Loading animation
void runLoaderAni() {
    // Only run when images are loading
    if (!checkLoadStates()) {
        ellipse(loaderX, loaderY, 10, 10);
        loaderX += 2;
        loaderY = height / 2 + sin(theta) * (height / 8);
        theta += PI / 22;
        // Reposition ellipse if it goes off the screen
        if (loaderX > width + 5) {
            loaderX = -5;
        }
    }
}

// Return true when all images are loaded - no false values left in array
bool checkLoadStates() {
    // for (int i = 0; i < imgs.size(); i++) { //@diff(std::vector)
    //     if (loadStates[i] == false) {
    //         return false;
    //     }
    // }
    return true;
}