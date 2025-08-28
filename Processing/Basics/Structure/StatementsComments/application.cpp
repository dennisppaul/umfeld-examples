/**
 * Statements and Comments. 
 * 
 * Statements are the elements that make up programs. 
 * The ";" (semi-colon) symbol is used to end statements.  
 * It is called the "statement terminator." 
 * Comments are used for making notes to help people better understand programs. 
 * A comment begins with two forward slashes ("//"). 
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    // The size function is a statement that tells the computer
    // how large to make the window.
    // Each function statement has zero or more parameters.
    // Parameters are data passed into the function
    // and are used as values for telling the computer what to do.
    size(640, 360);
}

void setup() {
}

void draw() {
    // The background function is a statement that tells the computer
    // which color (or gray value) to make the background of the display window
    background(.8f, .6f, 0.f); //@diff(color_range)
}
