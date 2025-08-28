/**
 * Storing Input. 
 * 
 * Move the mouse across the screen to change the position
 * of the circles. The positions of the mouse are recorded
 * into an array and played back every frame. Between each
 * frame, the newest value are added to the end of each array
 * and the oldest value is deleted. 
 */

#include "Umfeld.h"

using namespace umfeld;

int                num = 60;
std::vector<float> mx(num); //@diff(std::vector)
std::vector<float> my(num); //@diff(std::vector)

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    fill(1.f, 0.5f); //@diff(color_range)
}

void draw() {
    background(.2f); //@diff(color_range)

    // Cycle through the array, using a different entry on each frame.
    // Using modulo (%) like this is faster than moving all the values over.
    int which = frameCount % num;
    mx[which] = mouseX;
    my[which] = mouseY;

    for (int i = 0; i < num; i++) {
        // which+1 is the smallest (the oldest in the array)
        int index = (which + 1 + i) % num;
        ellipse(mx[index], my[index], i, i);
    }
}
