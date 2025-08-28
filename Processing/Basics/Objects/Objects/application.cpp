#include "Umfeld.h"

using namespace umfeld;

class MRect {
    int   w;    // single bar width
    float xpos; // rect xposition
    float h;    // rect height
    float ypos; // rect yposition
    float d;    // single bar distance
    float t;    // number of bars
public:
    MRect() { //@diff(default_constructor)
        w    = 0;
        xpos = 0;
        h    = 0;
        ypos = 0;
        d    = 0;
        t    = 0;
    }
    MRect(int iw, float ixp, float ih, float iyp, float id, float it) {
        w    = iw;
        xpos = ixp;
        h    = ih;
        ypos = iyp;
        d    = id;
        t    = it;
    }

    void move(float posX, float posY, float damping) {
        float dif = ypos - posY;
        if (abs(dif) > 1) {
            ypos -= dif / damping;
        }
        dif = xpos - posX;
        if (abs(dif) > 1) {
            xpos -= dif / damping;
        }
    }

    void display() {
        for (int i = 0; i < t; i++) {
            rect(xpos + (i * (d + w)), ypos, w, height * h);
        }
    }
};

MRect r1, r2, r3, r4;

void settings() {
    size(640, 360);
}

void setup() {
    fill(1.f, .8f); //@diff(color_range)
    noStroke();
    r1 = MRect(1, 134.0, 0.532, 0.1 * height, 10.0, 60.0);
    r2 = MRect(2, 44.0, 0.166, 0.3 * height, 5.0, 50.0);
    r3 = MRect(2, 58.0, 0.332, 0.4 * height, 10.0, 35.0);
    r4 = MRect(1, 120.0, 0.0498, 0.9 * height, 15.0, 60.0);
}

void draw() {
    background(0.f); //@diff(color_range)

    r1.display();
    r2.display();
    r3.display();
    r4.display();

    r1.move(mouseX - (width / 2), mouseY + (height * 0.1), 30);
    r2.move(int(mouseX + (width * 0.05)) % (int) width, mouseY + (height * 0.025), 20);
    r3.move(mouseX / 4, mouseY - (height * 0.025), 40);
    r4.move(mouseX - (width / 2), (height - mouseY), 50);
}