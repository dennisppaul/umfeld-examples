#pragma once
#include "Umfeld.h"

using namespace umfeld;

class HScrollbar {
public:
    int   swidth, sheight;  // width and height of bar
    float xpos, ypos;       // x and y position of bar
    float spos, newspos;    // x position of slider
    float sposMin, sposMax; // max and min values of slider
    int   loose;            // how loose/heavy
    bool  over;             // is the mouse over the slider?
    bool  locked;
    float ratio;
    bool* firstMousePress;

    HScrollbar() : firstMousePress(nullptr) {}
    HScrollbar(bool* firstMousePress) : firstMousePress(firstMousePress) {}


    HScrollbar(float xp, float yp, int sw, int sh, int l, bool* firstMousePress = nullptr) {
        swidth            = sw;
        sheight           = sh;
        int widthtoheight = sw - sh;
        ratio             = (float) sw / (float) widthtoheight;
        xpos              = xp;
        ypos              = yp - sheight / 2;
        spos              = xpos + swidth / 2 - sheight / 2;
        newspos           = spos;
        sposMin           = xpos;
        sposMax           = xpos + swidth - sheight;
        loose             = l;
        this->firstMousePress = firstMousePress;
    }

    void update() {
        if (overEvent()) {
            over = true;
        } else {
            over = false;
        }
        if (firstMousePress && over) {
            locked = true;
        }
        if (!isMousePressed) {
            locked = false;
        }
        if (locked) {
            newspos = constrain(mouseX - sheight / 2, sposMin, sposMax);
        }
        if (abs(newspos - spos) > 1) {
            spos = spos + (newspos - spos) / loose;
        }
    }

    float constrain(float val, float minv, float maxv) {
        return min(max(val, minv), maxv);
    }

    bool overEvent() { //@diff(generic_type)
        if (mouseX > xpos && mouseX < xpos + swidth &&
            mouseY > ypos && mouseY < ypos + sheight) {
            return true;
        } else {
            return false;
        }
    }

    void display() {
        noStroke();
        fill(.8f); //@diff(color_range)
        rect(xpos, ypos, swidth, sheight);
        if (over || locked) {
            fill(0.f); //@diff(color_range)
        } else {
            fill(.4f); //@diff(color_range)
        }
        rect(spos, ypos, sheight, sheight);
    }

    float getPos() {
        // Convert spos to be values between
        // 0 and the total width of the scrollbar
        return spos * ratio;
    }
};