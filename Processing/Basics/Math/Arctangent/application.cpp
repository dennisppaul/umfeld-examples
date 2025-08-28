/**
 * Arctangent. 
 * 
 * Move the mouse to change the direction of the eyes. 
 * The atan2() function computes the angle from each eye 
 * to the cursor. 
 */

#include "Umfeld.h"

using namespace umfeld;

class Eye { //@diff(forward_declaration)

private: //@diff(class_definition)
    int   x, y;
    int   size;
    float angle = 0.0;

public: //@diff(class_definition)

    Eye() = default; //@diff(default_constructor)
    Eye(int tx, int ty, int ts) {
        x    = tx;
        y    = ty;
        size = ts;
    }

    void update(int mx, int my) {
        angle = atan2(my - y, mx - x);
    }

    void display() {
        pushMatrix();
        translate(x, y);
        fill(1.f); //@diff(color_range)
        ellipse(0, 0, size, size);
        rotate(angle);
        fill(.6f, .8f, 0); //@diff(color_range)
        ellipse(size / 4, 0, size / 2, size / 2);
        popMatrix();
    }
};


Eye e1, e2, e3;

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    e1 = Eye(250,16,120);
    e2 = Eye(164, 185, 80);
    e3 = Eye(420, 230, 220);
}

void draw() {
    background(.4f); //@diff(color_range)

    e1.update(mouseX, mouseY);
    e2.update(mouseX, mouseY);
    e3.update(mouseX, mouseY);

    e1.display();
    e2.display();
    e3.display();
}
