/**
 * Koch Curve
 * by Daniel Shiffman.
 * 
 * Renders a simple fractal, the Koch snowflake. 
 * Each recursive level is drawn in sequence. 
 */

#include "Umfeld.h"
#include "KochFractal.h"

using namespace umfeld;

KochFractal k;

void settings() {
    size(640, 360);
}

void setup() {
    set_frame_rate(1); // Animate slowly //@diff(frameRate)
    k.init(); // Initialize after size is set
}

void draw() {
    background(0.f); //@diff(color_range)
    // Draws the snowflake!
    k.render();
    // Iterate
    k.nextLevel();
    // Let's not do it more than 5 times. . .
    if (k.getCount() > 5) {
        k.restart();
    }
}
