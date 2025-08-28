/**
 * Composite Objects
 * 
 * An object can include several other objects. Creating such composite objects 
 * is a good way to use the principles of modularity and build higher levels of 
 * abstraction within a program.
 */
#include "Umfeld.h"
#include "EggRing.h"

using namespace umfeld;

EggRing er1, er2;

void settings() {
    size(640, 360);
}

void setup() {
    er1 = EggRing(width * 0.45, height * 0.5, 2, 120);  //@diff(class_initializer)
    er2 = EggRing(width * 0.65, height * 0.8, 10, 180); //@diff(class_initializer)
}

void draw() {
    background(0.f); //@diff(color_range)
    er1.transmit();
    er2.transmit();
}
