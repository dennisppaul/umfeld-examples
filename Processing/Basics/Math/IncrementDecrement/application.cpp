/**
 * Increment Decrement. 
 * 
 * Writing "a++" is equivalent to "a = a + 1".  
 * Writing "a--" is equivalent to "a = a - 1".   
 */
#include "Umfeld.h"

using namespace umfeld;

int  b;
int  c;
bool direction;

void settings() {
    size(640, 360);
}

void setup() {
    //   colorMode(RGB, width);
    b         = 0;
    c         = width;
    direction = true;
    set_frame_rate(30); //@diff(set_frame_rate)
}

void draw() {
    b++;
    if (b > width) {
        b         = 0;
        direction = !direction;
    }
    if (direction == true) {
        stroke((float)b/width); //@diff(color_range)
    } else {
        stroke((float)(width - b)/width); //@diff(color_range)
    }
    line(b, 0, b, height / 2);

    c--;
    if (c < 0) {
        c = width;
    }
    if (direction == true) {
        stroke((float)(width - c)/width); //@diff(color_range)
    } else {
        stroke((float)c/width); //@diff(color_range)
    }
    line(c, height / 2 + 1, c, height);
}
