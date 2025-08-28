/**
 * Operator Precedence
 * 
 * If you don't direction state the order in which an 
 * expression is evaluated, it is decided by the operator 
 * precedence. For example, in the expression 4+2*8, the 
 * 2 will first be multiplied by 8 and then the result will 
 * be added to 4. This is because multiplication has a higher 
 * precedence than addition. To avoid ambiguity in reading 
 * the program, it is recommended to write the expression as 
 * 4+(2*8). The order of evaluation can be controlled through 
 * adding parenthesis in the code. 
 */

// The highest precedence is at the top of the list and
// the lowest is at the bottom.
// Multiplicative: * / %
// Additive: + -
// Bitwise shift: << >>
// Relational: < > <= >=
// Equality: == !=
// Bitwise AND: &
// Bitwise XOR: ^
// Bitwise OR: |
// Logical AND: &&
// Logical OR: ||
// Conditional (ternary): ? :
// Assignment: = += -= *= /= %= <<= >>= &= ^= |=

#include "Umfeld.h"

using namespace umfeld;


void settings() {
    size(640, 360);
}

void setup() {
    background(.2f); //@diff(color_range)
    noFill();
    stroke(.2f); //@diff(color_range)
}

void draw() {
    stroke(.8f); //@diff(color_range)
    for (int i = 0; i < width - 20; i += 4) {
        // The 30 is added to 70 and then evaluated
        // if it is greater than the current value of "i"
        // For clarity, write as "if (i > (30 + 70)) {"
        if (i > 30 + 70) {
            line(i, 0, i, 50);
        }
    }

    stroke(1.f); //@diff(color_range)
    // The 2 is multiplied by the 8 and the result is added to the 4
    // For clarity, write as "rect(5 + (2 * 8), 0, 90, 20);"
    rect(4 + 2 * 8, 52, 290, 48);
    rect((4 + 2) * 8, 100, 290, 49);

    stroke(.6f); //@diff(color_range)
    for (int i = 0; i < width; i += 2) {
        // The relational statements are evaluated
        // first, and then the logical AND statements and
        // finally the logical OR. For clarity, write as:
        // "if(((i > 20) && (i < 50)) || ((i > 100) && (i < width-20))) {"
        if (i > 20 && i < 50 || i > 100 && i < width - 20) {
            line(i, 151, i, height - 1);
        }
    }
}
/*
note:
- the top comment is adjusted to align with c++
*/