/**
 * Sequential
 * by James Paterson.  
 * 
 * Displaying a sequence of images creates the illusion of motion. 
 * Twelve images are loaded and each is displayed individually in a loop. 
 */

#include "Umfeld.h"

using namespace umfeld;

int                  numFrames    = 12; // The number of frames in the animation
int                  currentFrame = 0;
std::vector<PImage*> images(numFrames); //@diff(std::vector)

void settings() {
    size(640, 360);
}

void setup() {
    set_frame_rate(24); //@diff(frameRate)

    images[0]  = loadImage("PT_anim0000.gif");
    images[1]  = loadImage("PT_anim0001.gif");
    images[2]  = loadImage("PT_anim0002.gif");
    images[3]  = loadImage("PT_anim0003.gif");
    images[4]  = loadImage("PT_anim0004.gif");
    images[5]  = loadImage("PT_anim0005.gif");
    images[6]  = loadImage("PT_anim0006.gif");
    images[7]  = loadImage("PT_anim0007.gif");
    images[8]  = loadImage("PT_anim0008.gif");
    images[9]  = loadImage("PT_anim0009.gif");
    images[10] = loadImage("PT_anim0010.gif");
    images[11] = loadImage("PT_anim0011.gif");

    // If you don't want to load each image separately
    // and you know how many frames you have, you
    // can create the filenames as the program runs.
    // You can use the following code to load images dynamically,
    // in c++, we add a certain amount of zeros to number(zero-padding)
    // like this
    // for (int i = 0; i < numFrames; i++) {
    //     std::string filename = "PT_anim";
    //     std::stringstream ss;
    //     ss << std::setw(4) << std::setfill('0') << i; // Zero-pad the number to 4 digits (setw means "set the width")
    //     filename += ss.str() + ".gif";
    //     images[i] = loadImage(filename);
    // }    
    // This will load images from PT_anim0000.gif to PT_anim0011.gif
}

void draw() {
    background(0.f); //@diff(color_range)
    currentFrame = (currentFrame + 1) % numFrames; // Use % to cycle through frames
    int offset   = 0;
    for (int x = -100; x < width; x += images[0]->width) { //@diff(pointer)
        image(images[(currentFrame + offset) % numFrames], x, -20);
        offset += 2;
        image(images[(currentFrame + offset) % numFrames], x, height / 2);
        offset += 2;
    }
}