/**
 * Sine Wave
 * by Daniel Shiffman.  
 * 
 * Render a simple sine wave. 
 */

#include "Umfeld.h"

using namespace umfeld;

int xspacing = 16;   // How far apart should each horizontal location be spaced
int w;              // Width of entire wave

float theta = 0.0;  // Start angle at 0
float amplitude = 75.0;  // Height of wave
float period = 500.0;  // How many pixels before the wave repeats
float dx;  // Value for incrementing X, a function of period and xspacing
std::vector<float> yvalues;  // Using an array to store height values for the wave //@diff(std::vector)

void calcWave(); //@diff(forward_declaration)
void renderWave(); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    w = width+16;
    dx = (TWO_PI / period) * xspacing;
    yvalues = std::vector<float>(w/xspacing); //@diff(std::vector)
}

void draw() {
    background(0.f);
    calcWave();
    renderWave();
}

void calcWave() {
    // Increment theta (try different values for 'angular velocity' here
    theta += 0.02;

    // For every x value, calculate a y value with sine function
    float x = theta;
    for (int i = 0; i < yvalues.size(); i++) {
        yvalues[i] = sin(x)*amplitude;
        x+=dx;
    }
}

void renderWave() {
  noStroke();
  fill(1.f); //@diff(color_range)
  // A simple way to draw the wave with an ellipse at each location
  for (int x = 0; x < yvalues.size(); x++) {
    ellipse(x*xspacing, height/2+yvalues[x], 16, 16);
  }
}
