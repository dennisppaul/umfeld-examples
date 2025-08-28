/**
 * Letters. 
 * 
 * Draws letters to the screen. This requires loading a font, 
 * setting the font, and then drawing the letters.
 */

#include "Umfeld.h"

using namespace umfeld;

PFont* f; //@diff(pointer)

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)

    // Create the font
    // printArray(PFont.list()); //unimplemented
    // f = createFont("SourceCodePro-Regular.ttf", 24);
    f = loadFont("SourceCodePro-Regular.ttf", 24); //@diff(loadFont)
    textFont(f);
    textAlign(CENTER, CENTER);
}

void draw() {
    background(0.f); //@diff(color_range)

    // Set the left and top margin
    int margin = 10;
    translate(margin * 4, margin * 4);

    int gap     = 46;
    int counter = 35;

    for (int y = 0; y < height - gap; y += gap) {
        for (int x = 0; x < width - gap; x += gap) {

            char letter = char(counter);

            if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U') {
                fill(1.f, .8f, 0.f); //@diff(color_range)
            } else {
                fill(1.f); //@diff(color_range)
            }

            // Draw the letter to the screen
            text(letter, x, y);

            // Increment the counter
            counter++;
        }
    }
}