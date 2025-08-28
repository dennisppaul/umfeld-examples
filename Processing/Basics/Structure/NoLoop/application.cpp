/**
 * No Loop. 
 * 
 * The noLoop() function causes draw() to only run once. 
 * Without calling noLoop(), the code inside draw() is 
 * run continually. 
 */

#include "Umfeld.h"

using namespace umfeld;

float y = 180;

void settings() {
    size(1024, 768);
}

// The statements in the setup() block 
// run once when the program begins
void setup() {
  size(640, 360);  // Size should be the first statement
  stroke(1.f);  // Set line drawing color to white //@diff(color_range)
  noLoop();
}

// In this example, the code in the draw() block 
// runs only once because of the noLoop() in setup()
void draw() { 
  background(0.f);   // Set the background to black //@diff(color_range)
  line(0, y, width, y);  
  y = y - 1; 
  if (y < 0) { y = height; } 
} 
