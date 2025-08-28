/**
 * Random Gaussian. 
 * 
 * This sketch draws ellipses with x and y locations tied to a gaussian distribution of random numbers.
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
}

void draw() {

    // Get a gaussian random number w/ mean of 0 and standard deviation of 1.0
    float val = randomGaussian();

    float sd   = 60;                // Define a standard deviation
    float mean = width / 2;         // Define a mean value (middle of the screen along the x-axis)
    float x    = (val * sd) + mean; // Scale the gaussian random number by standard deviation and mean

    noStroke();
    fill(1.f, 0.04f); //@diff(color_range)
    ellipse(x, height / 2, 32, 32); // Draw an ellipse at our "normal" random location
}
