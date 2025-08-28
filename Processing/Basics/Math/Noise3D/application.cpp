/**
 * Noise3D. 
 * 
 * Using 3D noise to create simple animated texture. 
 * Here, the third dimension ('z') is treated as time. 
 */

#include "Umfeld.h"

using namespace umfeld;

float increment = 0.01;
// The noise function's 3rd argument, a global variable that increments once per cycle
float zoff = 0.0;
// We will increment zoff differently than xoff and yoff
float zincrement = 0.02;

void settings() {
    size(640, 360);
}

void setup() {
    set_frame_rate(30);
}

void draw() {

    // Optional: adjust noise detail here
    // noiseDetail(8,0.65f);

    loadPixels();

    float xoff = 0.0; // Start xoff at 0

    // For every x,y coordinate in a 2D space, calculate a noise value and produce a brightness value
    for (int x = 0; x < width; x++) {
        xoff += increment; // Increment xoff
        float yoff = 0.0;  // For every xoff, start yoff at 0
        for (int y = 0; y < height; y++) {
            yoff += increment; // Increment yoff

            // Calculate noise and scale by 255
            float bright = noise(xoff, yoff, zoff); //@diff(color_range)

            // Try using this line instead
            //float bright = random(0,255);

            // Set each pixel onscreen to a grayscale value
            pixels[x + y * (int)width] = color(bright, bright, bright); //@diff(color_range)
        }
    }
    updatePixels();

    zoff += zincrement; // Increment zoff
}
