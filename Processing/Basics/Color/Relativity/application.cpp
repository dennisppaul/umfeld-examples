/**
 * Relativity. 
 * 
 * Each color is perceived in relation to other colors. The top and bottom 
 * bars each contain the same component colors, but a different display order 
 * causes individual colors to appear differently. 
 */
 
#include "Umfeld.h"

using namespace umfeld;

// in the original example, the vars are a,b,c,d,e
// but the "a" becomes ambiguous(for compiler) inside umfeld,
// cuz there is a global definition of
// inline PAudio* a = nullptr; inside Umfeld.h
uint32_t c1, c2, c3, c4, c5; //@diff(color_type)

void drawBand(uint32_t v, uint32_t w, uint32_t x, uint32_t y, uint32_t z, int ypos, int barWidth); //@diff(forward_definition)

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    //@diff(color_range, color_tyle)
    c1 = color(165.f / 255.f, 167.f / 255.f, 20.f / 255.f);
    c2 = color(77.f / 255.f, 86.f / 255.f, 59.f / 255.f);
    c3 = color(42.f / 255.f, 106.f / 255.f, 105.f / 255.f);
    c4 = color(165.f / 255.f, 89.f / 255.f, 20.f / 255.f);
    c5 = color(146.f / 255.f, 150.f / 255.f, 127.f / 255.f);
    noLoop(); // Draw only one time
}

void draw() {
    drawBand(c1, c2, c3, c4, c5, 0, width / 128);
    drawBand(c3, c1, c4, c2, c5, height / 2, width / 128);
}

void drawBand(uint32_t v, uint32_t w, uint32_t x, uint32_t y, uint32_t z, int ypos, int barWidth) {
    int num = 5;
    std::vector<uint32_t> colorOrder = {v, w, x, y, z}; 
    for (int i = 0; i < width; i += barWidth * num) {
        for (int j = 0; j < num; j++) {
            fill_color(colorOrder[j]); // fill vs fill_color ambiguous(humanely)
            rect(i + j * barWidth, ypos, barWidth, height / 2);
        }
    }
}