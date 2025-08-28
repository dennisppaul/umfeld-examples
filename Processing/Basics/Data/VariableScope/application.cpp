/**
 * Variable Scope. 
 * 
 * Variables have a global or local "scope". 
 * For example, variables declared within either the
 * setup() or draw() functions may be only used in these
 * functions. Global variables, variables declared outside
 * of setup() and draw(), may be used anywhere within the program.
 * If a local variable is declared with the same name as a
 * global variable, the program will use the local variable to make 
 * its calculations within the current scope. Variables are localized
 * within each block, the space between a { and }. 
 */
#include "Umfeld.h"

using namespace umfeld;
// a is audio in umfeld
int b = 80; // Create a global variable "b"

void drawYetAnotherLine(); // @diff(forward_declaration)
void drawAnotherLine();    // @diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
    stroke(1.f);     //@diff(color_range)
    noLoop();
}

void draw() {
    // Draw a line using the global variable "b"
    line(b, 0, b, height);

    // Create a new variable "b" local to the for() statement
    for (int b = 120; b < 200; b += 2) {
        line(b, 0, b, height);
    }

    // Create a new variable "b" local to the draw() function
    int b = 300;
    // Draw a line using the new local variable "b"
    line(b, 0, b, height);

    // Make a call to the custom function drawAnotherLine()
    drawAnotherLine();

    // Make a call to the custom function setYetAnotherLine()
    drawYetAnotherLine();
}

void drawAnotherLine() {
    // Create a new variable "b" local to this method
    int b = 320;
    // Draw a line using the local variable "b"
    line(b, 0, b, height);
}

void drawYetAnotherLine() {
    // Because no new local variable "b" is set,
    // this line draws using the original global
    // variable "b", which is set to the value 80.
    line(b + 2, 0, b + 2, height);
}
