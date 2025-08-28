#pragma once

#include "Umfeld.h"


class Module {
public:

    int   xOffset;
    int   yOffset;
    float x, y;
    int   unit;
    int   xDirection = 1;
    int   yDirection = 1;
    float speed;

    // Default constructor
    Module() : xOffset(0), yOffset(0), x(0), y(0), unit(0), speed(0) {}

    // Contructor
    Module(int xOffsetTemp, int yOffsetTemp, int xTemp, int yTemp, float speedTemp, int tempUnit) {
        xOffset = xOffsetTemp;
        yOffset = yOffsetTemp;
        x       = xTemp;
        y       = yTemp;
        speed   = speedTemp;
        unit    = tempUnit;
    }
    ~Module() = default; //@diff(destructor)

    // Custom method for updating the variables
    void update() {
        x = x + (speed * xDirection);
        if (x >= unit || x <= 0) {
            xDirection *= -1;
            x = x + (1 * xDirection);
            y = y + (1 * yDirection);
        }
        if (y >= unit || y <= 0) {
            yDirection *= -1;
            y = y + (1 * yDirection);
        }
    }

    // Custom method for drawing the object
    void display() {
        umfeld::fill(1.f);
        umfeld::ellipse(xOffset + x, yOffset + y, 6, 6);
    }
};