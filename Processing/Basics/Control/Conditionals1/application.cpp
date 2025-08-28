/**
 * Conditionals 1. 
 * 
 * Conditions are like questions. 
 * They allow a program to decide to take one action if 
 * the answer to a question is "true" or to do another action
 * if the answer to the question is "false." 
 * The questions asked within a program are always logical
 * or relational statements. For example, if the variable 'i' is 
 * equal to zero then draw a line. 
 */
 
#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
}

void draw() {
    background(0.f); //@diff(color_range)

    for (int i = 10; i < width; i += 10) {
        // If 'i' divides by 20 with no remainder draw
        // the first line, else draw the second line
        if ((i % 20) == 0) {
            stroke(1.f); //@diff(color_range)
            line(i, 80, i, height / 2);
        } else {
            stroke(1.f); //@diff(color_range)
            line(i, 20, i, 180);
        }
    }
}
