/**
 * Zoom. 
 * 
 * Move the cursor over the image to alter its position. Click and press
 * the mouse to zoom. This program displays a series of lines with their 
 * heights corresponding to a color value read from an image. 
 */


#include "Umfeld.h"

using namespace umfeld;

PImage* img;
std::vector<std::vector<int>> imgPixels; //@diff(std::vector)
float sval = 1.0;
float nmx, nmy;
int   res = 5;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    noFill();
    stroke(1.f); //@diff(color_range)
    img = loadImage("ystone08.jpg");
    imgPixels = std::vector<std::vector<int>>(img->width, std::vector<int>(img->height)); //@diff(std::vector)
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            imgPixels[j][i] = img->get(j, i);
        }
    }
}

void draw() {
    background(0.f); //@diff(color_range)

    nmx += (mouseX - nmx) / 20;
    nmy += (mouseY - nmy) / 20;

    if (isMousePressed) {
        sval += 0.005;
    } else {
        sval -= 0.01;
    }

    sval = constrain(sval, 1.f, 2.f);

    translate(width / 2 + nmx * sval - 100, height / 2 + nmy * sval - 100, -50);
    scale(sval);
    rotateZ(PI / 9 - sval + 1.0);
    rotateX(PI / sval / 8 - 0.125);
    rotateY(sval / 8 - 0.125);

    translate(-width / 2, -height / 2, 0);

    for (int i = 0; i < img->height; i += res) {
        for (int j = 0; j < img->width; j += res) {
            float rr = red(imgPixels[j][i]) * 255.0f; // Convert to 0-255 range
            float gg = green(imgPixels[j][i]) * 255.0f; // Convert to 0-255 range
            float bb = blue(imgPixels[j][i]) * 255.0f; // Convert to 0-255 range
            float tt = rr + gg + bb;
            stroke(rr/255.0f, gg/255.0f, bb/255.0f); // Convert back to 0-1 range for stroke
            line(j, i, tt / 10 - 20, j, i, tt / 10); // Fixed coordinate order
        }
    }
}
