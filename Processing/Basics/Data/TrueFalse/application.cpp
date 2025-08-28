/**
 * True/False. 
 * 
 * A Boolean variable has only two possible values: true or false. 
 * It is common to use Booleans with control statements to 
 * determine the flow of a program. In this example, when the
 * boolean value "x" is true, vertical black lines are drawn and when
 * the boolean value "x" is false, horizontal gray lines are drawn. 
 */

#include "Umfeld.h"

using namespace umfeld;

bool b = false; //@diff(generic_type)


void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
    stroke(1.f); //@diff(color_range)
}

void draw() {

    int d      = 20;
    int middle = width / 2;

    for (int i = d; i <= width; i += d) {

        if (i < middle) {
            b = true;
        } else {
            b = false;
        }

        if (b == true) {
            // Vertical line
            line(i, d, i, height - d);
        }

        if (b == false) {
            // Horizontal line
            line(middle, i - middle + d, width - d, i - middle + d);
        }
    }
}
