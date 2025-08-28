/**
 * Saturation. 
 * 
 * Saturation is the strength or purity of the color and represents the 
 * amount of gray in proportion to the hue. A "saturated" color is pure 
 * and an "unsaturated" color has a large percentage of gray. 
 * Move the cursor vertically over each bar to alter its saturation. 
 */
#include "Umfeld.h"
#include "glm/gtx/color_space.hpp"

using namespace umfeld;

int barWidth = 20;
int lastBar  = -1;

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
}

void draw() {
    float whichBar = mouseX / barWidth;
    if (whichBar != lastBar) {
        int barX = whichBar * barWidth;

        glm::vec3 hsb(
            (float) barX / width * 360.0f, // glm expects hue in degrees 0-360
            mouseY / height,
            .66f);

        glm::vec3 rgb = glm::rgbColor(hsb);
        fill(rgb.r, rgb.g, rgb.b);
        rect(barX, 0, barWidth, height);
        lastBar = whichBar;
    }
}