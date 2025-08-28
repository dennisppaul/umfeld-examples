/**
 * Brownian motion. 
 * 
 * Recording random movement as a continuous line. 
 */
#include "Umfeld.h"

using namespace umfeld;

int num   = 2000;
int range = 6;

std::vector<float> ax(num); //@diff(std::vector)
std::vector<float> ay(num); //@diff(std::vector)

void settings() {
    size(640, 360);
}

void setup() {
    for (int i = 0; i < num; i++) {
        ax[i] = width / 2;
        ay[i] = height / 2;
    }
    set_frame_rate(30); //@diff(frameRate)
}

void draw() {
    background(.2f); //@diff(color_range)

    // Shift all elements 1 place to the left
    for (int i = 1; i < num; i++) {
        ax[i - 1] = ax[i];
        ay[i - 1] = ay[i];
    }

    // Put a new value at the end of the array
    ax[num - 1] += random(-range, range);
    ay[num - 1] += random(-range, range);

    // Constrain all points to the screen
    ax[num - 1] = constrain(ax[num - 1], 0.f, width);
    ay[num - 1] = constrain(ay[num - 1], 0.f, height);

    // Draw a line connecting the points
    for (int i = 1; i < num; i++) {
        float val = (float(i) / num * 204.0 + 51) / 255.f; //@diff(color_range)
        stroke(val);
        line(ax[i - 1], ay[i - 1], ax[i], ay[i]);
    }
}