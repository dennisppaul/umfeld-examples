#pragma once
#include "Egg.h"
#include "Ring.h"

class EggRing {
    Egg  ovoid;
    Ring circle;

public:

    EggRing() = default; //@diff(default_constructor)

    EggRing(float x, float y, float t, float sp) {
        ovoid = Egg(x, y, t, sp);
        circle.start(x, y - sp / 2);
    }

    void transmit() {
        ovoid.wobble();
        ovoid.display();
        circle.grow();
        circle.display();
        if (circle.on == false) {
            circle.on = true;
        }
    }
};
