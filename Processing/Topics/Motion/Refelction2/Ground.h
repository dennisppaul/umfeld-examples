#pragma once
#include "Umfeld.h"

class Ground {
public:
    float x1, y1, x2, y2;
    float x, y, len, rot;

    // Constructor
    Ground() : x1(0), y1(0), x2(0), y2(0), x(0), y(0), len(0), rot(0) {}

    Ground(float x1, float y1, float x2, float y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x = (x1 + x2) / 2;
        this->y = (y1 + y2) / 2;
        this->len = umfeld::dist(x1, y1, x2, y2);
        this->rot = std::atan2f((y2 - y1), (x2 - x1));
    }
};