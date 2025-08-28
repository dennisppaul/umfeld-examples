/**
 * Points and Lines. 
 * 
 * Points and lines can be used to draw basic geometry.
 * Change the value of the variable 'd' to scale the form.
 * The four variables set the positions based on the value of 'd'. 
 */

#include "Umfeld.h"

using namespace umfeld;

int d  = 70;
int p1 = d;
int p2 = p1 + d;
int p3 = p2 + d;
int p4 = p3 + d;

void settings() {
    size(640, 360);
}

void setup() {

    size(640, 360);
    hint(DISABLE_SMOOTH_LINES); //@diff(available_hints)
    background(0.f); //@diff(color_range)
    translate(140, 0);
}

void draw() {
    // Draw gray box
    stroke(0.5f);
    line(p3, p3, p2, p3);
    line(p2, p3, p2, p2);
    line(p2, p2, p3, p2);
    line(p3, p2, p3, p3);

    // Draw white points
    stroke(1.f);
    point(p1, p1); //FIXME: DOES NOT DRAW ANYTHING
    point(p1, p3); //FIXME: DOES NOT DRAW ANYTHING
    point(p2, p4); //FIXME: DOES NOT DRAW ANYTHING
    point(p3, p1); //FIXME: DOES NOT DRAW ANYTHING
    point(p4, p2); //FIXME: DOES NOT DRAW ANYTHING
    point(p4, p4); //FIXME: DOES NOT DRAW ANYTHING
}
