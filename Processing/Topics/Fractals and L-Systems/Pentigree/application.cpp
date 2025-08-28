/** 
 * Pentigree L-System 
 * by Geraldine Sarmiento. 
 * 
 * This example was based on Patrick Dwyer's L-System class. 
 */

#include "Umfeld.h"
#include "PentigreeLSystem.h"
using namespace umfeld;

PentigreeLSystem ps;

void settings() {
    size(640, 360);
}


void setup() {
    ps.simulate(3);
}

void draw() {
    background(0.f); //@diff(color_range)
    ps.render();
}
