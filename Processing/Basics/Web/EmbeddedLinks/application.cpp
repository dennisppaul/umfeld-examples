/**
 * Loading URLs. 
 * 
 * Click on the button to open a URL in a browser.
 */

#include "Umfeld.h"

using namespace umfeld;

bool overButton = false; //@diff(generic_type)

void checkButtons(); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
}

void draw() {
    background(.8f); //@diff(color_range)

    if (overButton == true) {
        fill(1.f); //@diff(color_range)
    } else {
        noFill();
    }
    rect(105, 60, 75, 75);
    line(135, 105, 155, 85);
    line(140, 85, 155, 85);
    line(155, 85, 155, 100);
}

void mousePressed() {
    if (overButton) {
        // link("https://github.com/dennisppaul/umfeld"); //unimplemented
    }
}

void mouseMoved() {
    checkButtons();
}

void mouseDragged() {
    checkButtons();
}

void checkButtons() {
    if (mouseX > 105 && mouseX < 180 && mouseY > 60 && mouseY < 135) {
        overButton = true;
    } else {
        overButton = false;
    }
}
