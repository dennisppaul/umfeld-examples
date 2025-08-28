/**
 * Logical Operators. 
 * 
 * The logical operators for AND (&&) and OR (||) are used to 
 * combine simple relational statements into more complex expressions.
 * The NOT (!) operator is used to negate a boolean statement. 
 */

#include "Umfeld.h"

using namespace umfeld;

bool test = false; //@diff(generic_type)

void settings() {
    size(640, 360);
}

void setup() {
    background(0.5f); //@diff(color_range)
}

void draw() {
    for (int i = 5; i <= height; i += 5) {
        // Logical AND
        stroke(0.f); //@diff(color_range)
        if ((i > 35) && (i < 100)) {
            line(width / 4, i, width / 2, i);
            test = false;
        }

        // Logical OR
        stroke(0.3f); //@diff(color_range)
        if ((i <= 35) || (i >= 100)) {
            line(width / 2, i, width, i);
            test = true;
        }

        // Testing if a boolean value is "true"
        // The expression "if(test)" is equivalent to "if(test == true)"
        if (test) {
            stroke(0.f); //@diff(color_range)
            point(width / 3, i); // FIXME: THIS DOES NOT WORK
        }

        // Testing if a boolean value is "false"
        // The expression "if(!test)" is equivalent to "if(test == false)"
        if (!test) {
            stroke(1.f); //@diff(color_range)
            point(width / 4, i); // FIXME: THIS DOES NOT WORK
        }
    }
}
