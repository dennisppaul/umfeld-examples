#include "Umfeld.h"

using namespace umfeld;

PImage* myImage;

void settings() {
    size(1024, 768);
}

void setup() {
    myImage = loadImage("drip.png");
}

void draw() {
    const int halfImage = width * height / 2;
    image(myImage, 0, 0);

    loadPixels();
    for (int i = 0; i < halfImage; i++) {
        pixels[i + halfImage] = pixels[i];
    }
    constexpr int offset = 10;
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            const int i           = (x + offset) + (y + offset) * width;
            pixels[i + halfImage] = color(1.0f);
        }
    }
    updatePixels();

    noStroke();
    fill(1.0f);
    debug_text("FPS: " + to_string(frameRate), 10, 20);
}
