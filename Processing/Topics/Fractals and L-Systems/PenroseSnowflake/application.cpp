/** 
 * Penrose Snowflake L-System 
 * by Geraldine Sarmiento. 
 * 
 * This example was based on Patrick Dwyer's L-System class. 
 */

#include "Umfeld.h"
#include "PenroseSnowflakeLSystem.h"

using namespace umfeld;

PenroseSnowflakeLSystem ps;

void settings() {
    size(640, 360);
}

void setup() {
    stroke(1.f); //@diff(color_range)
    noFill();
    ps.simulate(4);
}

void draw() {
    background(0.f); //@diff(color_range)
    ps.render();
}
