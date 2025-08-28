/**
 * Milliseconds. 
 * 
 * A millisecond is 1/1000 of a second. 
 * Processing keeps track of the number of milliseconds a program has run.
 * By modifying this number with the modulo(%) operator, 
 * different patterns in time are created.  
 */

#include "Umfeld.h"

using namespace umfeld;

float s; //scale; scale is a global variable in Umfeld.h

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    s = width / 20;
}

void draw() {
    for (int i = 0; i < s; i++) {
        fill(
            (millis() % int((i + 1) * s * 10)) 
            / float((i + 1) * s * 10)
        ); //@diff(color_range)
        rect(i * s, 0, s, height);
    }
}
