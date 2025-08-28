/**
 * Noise1D. 
 * 
 * Using 1D Perlin Noise to assign location. 
 */
 
#include "Umfeld.h"

using namespace umfeld;

float xoff       = 0.0;
float xincrement = 0.01;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
    noStroke();
}

void draw() {
  // Create an alpha blended background
  fill(0, 0.04f); //@diff(color_range)
  rect(0,0,width,height);
  
  //float n = random(0,width);  // Try this line instead of noise
  
  // Get a noise value based on xoff and scale it according to the window's width
  float n = noise(xoff)*width;
  
  // With each cycle, increment xoff
  xoff += xincrement;
  
  // Draw the ellipse at the value produced by perlin noise
  fill(0.8f); //@diff(color_range)
  ellipse(n,height/2, 64, 64);
}
