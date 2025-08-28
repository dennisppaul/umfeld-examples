/**
 * Disable Style 
 * by George Brower.
 * 
 * Shapes are loaded with style information that tells them how
 * to draw (e.g. color, stroke weight). The disableStyle() 
 * method of PShape turns off this information so functions like
 * stroke() and fill() change the SVGs color. The enableStyle()
 * method turns the file's original styles back on.
 */

// PShape bot;

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    // The file "bot1.svg" must be in the data folder
    // of the current sketch to load successfully
    // bot = loadShape("bot1.svg"); // unimplemented
    noLoop();
}

void draw() {
    background(.4f); //@diff(color_range)

    // Draw left bot
    // bot.disableStyle(); // Ignore the colors in the SVG
    fill(0, .4f, .6f);  // Set the SVG fill to blue //@diff(color_range)
    stroke(1.f);        // Set the SVG fill to white //@diff(color_range)
    // shape(bot, 20, 25, 300, 300);

    // Draw right bot
    // bot.enableStyle();
    // shape(bot, 320, 25, 300, 300);
}
