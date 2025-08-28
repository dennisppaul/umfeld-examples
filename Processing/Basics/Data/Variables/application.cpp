/**
 * Variables. 
 * 
 * Variables are used for storing values. In this example, change 
 * the values of variables to affect the composition. 
 */
#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f);
    stroke(0.6f);
    strokeWeight(4);
    strokeCap(SQUARE);
}

void draw() {
    int d = 50;
    int e = 120;
    int f = 180;

    line(d, e, d + f, e);
    line(d, e + 10, d + f, e + 10);
    line(d, e + 20, d + f, e + 20);
    line(d, e + 30, d + f, e + 30);

    d = d + f;
    e = height - e;

    line(d, e, d + f, e);
    line(d, e + 10, d + f, e + 10);
    line(d, e + 20, d + f, e + 20);
    line(d, e + 30, d + f, e + 30);

    d = d + f;
    e = height - e;

    line(d, e, d + f, e);
    line(d, e + 10, d + f, e + 10);
    line(d, e + 20, d + f, e + 20);
    line(d, e + 30, d + f, e + 30);
}
