/**
 * Handles.
 *
 * Click and drag the white boxes to change their position.
 */

#include "Umfeld.h"
#include "Handle.h"

using namespace umfeld;

std::vector<Handle> handles;

//True if a mouse button has just been pressed while no other button was.
bool firstMousePress = false; //@diff(generic_type)

void settings() {
    size(640, 360);
}

void setup() {
    int num   = height / 15;
    handles   = std::vector<Handle>(num); //@diff(std::vector)
    int hsize = 10;
    for (int i = 0; i < handles.size(); i++) {
        handles[i] = Handle(width / 2, 10 + i * 15, 50 - hsize / 2, 10, handles, firstMousePress);
    }
}

void draw() {
    background(.6f); //@diff(color_range)

    for (int i = 0; i < handles.size(); i++) {
        handles[i].update();
        handles[i].display();
    }

    fill(0);
    rect(0, 0, width / 2, height);

    //After it has been used in the sketch, set it back to false
    if (firstMousePress) {
        firstMousePress = false;
    }
}


void mousePressed() {
    if (!firstMousePress) {
        firstMousePress = true;
    }
}

void mouseReleased() {
    for (int i = 0; i < handles.size(); i++) {
        handles[i].releaseEvent();
    }
}
