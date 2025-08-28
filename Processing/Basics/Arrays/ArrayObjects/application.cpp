/**
 * Array Objects. 
 * 
 * Demonstrates the syntax for creating an array of custom objects. 
 */

#include "Umfeld.h"
#include "module.h"

using namespace umfeld;

int                 unit = 40;
int                 count;
std::vector<Module> mods; // @diff(std::vector)

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    int wideCount = width / unit;
    int highCount = height / unit;
    count         = wideCount * highCount;
    mods          = std::vector<Module>(count);

    int index = 0;
    for (int y = 0; y < highCount; y++) {
        for (int x = 0; x < wideCount; x++) {
            mods[index++] = Module(
                x * unit,
                y * unit,
                (int) (unit / 2),
                (int) (unit / 2),
                random(0.05, 0.8),
                unit
            );
        }
    }
}

void draw() {
    background(0.f);
    for (Module& mod: mods) { // @diff(range_based_for_loop)
        mod.update();
        mod.display();
    }
}
