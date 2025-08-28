#pragma once
#include "Umfeld.h"

using namespace umfeld;

// A Bubble class

class Bubble {
public:
    float       x, y;
    float       diameter;
    std::string name;

    bool over = false;

    // Create  the Bubble
    Bubble(float x_, float y_, float diameter_, std::string s) {
        x        = x_;
        y        = y_;
        diameter = diameter_;
        name     = s;
    }

    // Checking if mouse is over the Bubble
    void rollover(float px, float py) {
        float d = dist(px, py, x, y);
        if (d < diameter / 2) {
            over = true;
        } else {
            over = false;
        }
    }

    // Display the Bubble
    void display() {
        stroke(0.f); //@diff(color_range)
        strokeWeight(2);
        noFill();
        ellipse(x, y, diameter, diameter);
        if (over) {
            fill(0.f); //@diff(color_range)
            textAlign(CENTER);
            text(name, x, y + diameter / 2 + 20);
        }
    }
};
