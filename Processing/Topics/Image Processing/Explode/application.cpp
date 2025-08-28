/**
 * Explode 
 * by Daniel Shiffman. 
 * 
 * Mouse horizontal location controls breaking apart of image and 
 * Maps pixels from a 2D image into 3D space. Pixel brightness controls 
 * translation along z axis. 
 */
#include "Umfeld.h"

using namespace umfeld;

PImage* img;           // The source image
int     cellsize = 2;  // Dimensions of each cell in the grid
int     columns, rows; // Number of columns and rows in our system

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    img     = loadImage("eames.jpg"); // Load the image
    columns = img->width / cellsize;  // Calculate # of columns
    rows    = img->height / cellsize; // Calculate # of rows
}

void draw() {
    background(0.f); //@diff(color_range)
    // Begin loop for columns
    for (int i = 0; i < columns; i++) {
        // Begin loop for rows
        for (int j = 0; j < rows; j++) {
            int x   = i * cellsize + cellsize / 2; // x position
            int y   = j * cellsize + cellsize / 2; // y position
            int loc = x + y * img->width;          // Pixel array location
            uint32_t c   = img->pixels[loc]; //Grab the color //@diff(color_type)
            // Calculate a z position as a function of mouseX and pixel brightness
            float z = (mouseX / float(width)) * brightness(img->pixels[loc]) * 255.0f - 20.0;
            // Translate to the location, set fill and stroke, and draw the rect
            pushMatrix();
            translate(x + 200, y + 100, z);
            float r, g, b, a;
            color_unpack(c, r, g, b, a); // Unpack the color into
            fill(r, g, b, 0.8f); // Use RGB components with alpha //@diff(color_range)
            noStroke();
            rectMode(CENTER);
            rect(0, 0, cellsize, cellsize);
            popMatrix();
        }
    }
}
