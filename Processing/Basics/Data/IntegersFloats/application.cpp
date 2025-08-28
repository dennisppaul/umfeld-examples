/**
 * Integers Floats. 
 * 
 * Integers and floats are two different kinds of numerical data. 
 * An integer (more commonly called an int) is a number without 
 * a decimal point. A float is a floating-point number, which means 
 * it is a number that has a decimal place. Floats are used when
 * more precision is needed. 
 */
#include "Umfeld.h"

using namespace umfeld;
// a is audio in umfeld
int i = 0;      // Create a variable "i" of the datatype "int"
float f = 0.f;  // Create a variable "f" of the datatype "float"

void settings() {
    size(640, 360);
}

void setup() {
    stroke(1.f); //@diff(color_range)
}

void draw() {
    background(0.f); //@diff(color_range)

    i = i + 1;
    f = f + 0.2;
    line(i, 0, i, height / 2);
    line(f, height / 2, f, height);

    if (i > width) {
        i = 0;
    }
    if (f > width) {
        f = 0;
    }
}
