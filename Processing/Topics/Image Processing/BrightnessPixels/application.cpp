/**
 * Brightness Pixels
 * by Daniel Shiffman.
 *
 * This program adjusts the brightness of a part of the image by
 * calculating the distance of each pixel to the mouse.
 */

#include "Umfeld.h"

using namespace umfeld;

PImage* img;

void settings() {
    size(640, 360);
}

void setup() {
    set_frame_rate(30); //@diff(frameRate)
    img = loadImage("moon-wide.jpg");
    // img->loadPixels(g); //note: umfeld:: image pixels are already loaded
    // Only need to load the pixels[] array once, because we're only
    // manipulating pixels[] inside draw(), not drawing shapes.
    loadPixels();
}

void draw() {
    // First copy the original image pixels to the screen pixels array
    loadPixels();
    for (int i = 0; i < img->width * img->height; i++) {
        pixels[i] = img->pixels[i];
    }

    // Then modify the screen pixels based on mouse proximity
    for (int x = 0; x < img->width; x++) {
        for (int y = 0; y < img->height; y++) {
            // Calculate the 1D location from a 2D grid
            int loc = x + y * img->width;
            // Get the R,G,B values from the current screen pixel
            float r, g, b;
            r = red(pixels[loc]);
            g = green(pixels[loc]);
            b = blue(pixels[loc]);
            // Calculate an amount to change brightness based on proximity to the mouse
            float maxdist          = 50; //dist(0,0,width,height);
            float d                = dist(x, y, (int) mouseX, (int) mouseY);
            float adjustbrightness = (maxdist - d) / maxdist; //@diff(color_range)
            r += adjustbrightness;
            g += adjustbrightness;
            b += adjustbrightness;
            // Constrain RGB to make sure they are within 0-255 color range
            r = constrain(r, 0.f, 1.f); //@diff(color_range)
            g = constrain(g, 0.f, 1.f);
            b = constrain(b, 0.f, 1.f);
            // Make a new color and set pixel in the window
            uint32_t c                  = color(r, g, b);
            pixels[y * (int) width + x] = c;
        }
    }
    updatePixels();
}
