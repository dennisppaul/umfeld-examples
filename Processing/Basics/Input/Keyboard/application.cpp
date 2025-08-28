/**
 * Keyboard. 
 * 
 * Click on the image to give it focus and press the letter keys 
 * to create forms in time and space. Each key has a unique identifying 
 * number. These numbers can be used to position shapes in space. 
 */

#include "Umfeld.h"

using namespace umfeld;

int rectWidth;

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    background(0.f); //@diff(color_range)
    rectWidth = width / 4;
}

void draw() {
    // keep draw() here to continue looping while waiting for keys
}

void keyPressed() {
    int keyIndex = -1;
    if (key >= 'A' && key <= 'Z') {
        keyIndex = key - 'A';
    } else if (key >= 'a' && key <= 'z') {
        keyIndex = key - 'a';
    }
    if (keyIndex == -1) {
        // If it's not a letter key, clear the screen
        background(0.f); //@diff(color_range)
    } else {
        // It's a letter key, fill a rectangle
        float colorValue = float(millis() % 255) / 255.f; //@diff(color_range)
        fill(colorValue); //@diff(color_range)

        float x = map(keyIndex, 0, 25, 0, width - rectWidth);
        rect(x, 0, rectWidth, height);
    }
}

/*
note:
- drawing doesn't work inside the keyPressed() 
- i guess it is threaded and isn't taken into the gl context
- which is good, cuz the gl context shall live only in the main thread.
- I might rewrite it to work with the main thread.
*/