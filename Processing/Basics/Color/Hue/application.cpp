/**
 * Hue. 
 * 
 * Hue is the color reflected from or transmitted through an object 
 * and is typically referred to as the name of the color such as 
 * red, blue, or yellow. In this example, move the cursor vertically 
 * over each bar to alter its hue. 
 */
 
#include "Umfeld.h"
#include "glm/gtx/color_space.hpp"

using namespace umfeld;

int barWidth = 20;
int lastBar = -1;

void settings() {
  size(640, 360);
}

void setup() {
  noStroke();
  background(0.0f); //@diff(color_range)
}

void draw() {
  int whichBar = mouseX / barWidth;
  if (whichBar != lastBar) {
    int barX = whichBar * barWidth;
    
    // normalize the hsv values to the range 0-1
    float hue = mouseY / float(height);
    float saturation = 1.0f;
    float brightness = 1.0f;
    
    // use glm functions to convert HSV to RGB
    glm::vec3 hsv(hue * 360.0f, saturation, brightness);
    glm::vec3 rgb = glm::rgbColor(hsv);
    
    fill(rgb.r, rgb.g, rgb.b);
    rect(barX, 0, barWidth, height);
    lastBar = whichBar;
  }
}
