/** 
 * Penrose Tile L-System 
 * by Geraldine Sarmiento.
 *  
 * This example was based on Patrick Dwyer's L-System class. 
 */
#include "Umfeld.h"
#include "PenroseLSystem.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

PenroseLSystem ds;

void setup() {
    ds.simulate(4);
}

void draw() {
    background(0.f); //@diff(color_range)
    ds.render();
}
