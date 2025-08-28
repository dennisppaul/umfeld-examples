/**
 * Brightness 
 * by Rusty Robison. 
 * 
 * Brightness is the relative lightness or darkness of a color.
 * Move the cursor vertically over each bar to alter its brightness. 
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
    background(0.0f);
}

void draw() {
    int whichBar = mouseX / barWidth;
    if (whichBar != lastBar) {
        int barX = whichBar * barWidth;

        // the glm rgbColor function expects the hue to be in degrees (0-360), saturation (0-1), and brightness (0-1).
        glm::vec3 hsv(
            // hue: 0~width -> 0~360
            (static_cast<float>(barX) / width) * 360.0f, 
            // saturation: always max 100% -> 1.0
            1.0f, 
            // brightness: 0~height -> 0~1
            static_cast<float>(mouseY) / height 
        );

        // Use GLM to convert HSV to RGB
        glm::vec3 rgb = glm::rgbColor(hsv);
        fill(rgb.r, rgb.g, rgb.b);
        rect(barX, 0, barWidth, height);
        lastBar = whichBar;
    }
}