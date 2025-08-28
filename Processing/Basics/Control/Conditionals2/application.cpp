#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
}

void draw() {
    for (int i = 2; i < width - 2; i += 2) {
        // If 'i' divides by 20 with no remainder
        if ((i % 20) == 0) {
            stroke(1.f); //@diff(color_range)
            line(i, 80, i, height / 2);
            // If 'i' divides by 10 with no remainder
        } else if ((i % 10) == 0) {
            stroke(0.6f); //@diff(color_range)
            line(i, 20, i, 180);
            // If neither of the above two conditions are met
            // then draw this line
        } else {
            stroke(0.4f);//@diff(color_range)
            line(i, height / 2, i, height - 20);
        }
    }
}
