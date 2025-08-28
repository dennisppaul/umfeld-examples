/**
 * Simple Linear Gradient 
 * 
 * The lerpColor() function is useful for interpolating
 * between two colors.
 */
#include "Umfeld.h"

using namespace umfeld;

int      Y_AXIS = 1;
int      X_AXIS = 2;
uint32_t b1, b2, c1, c2; //@diff(color_type)

void setGradient(int x, int y, float w, float h, uint32_t c1, uint32_t c2, int axis); //@diff(forward_declaration)


void settings() {
    size(640, 360);
}

void setup() {
    b1 = color(1.f); //@diff(color_range)
    b2 = color(0.f); //@diff(color_range)
    c1 = color(0.8f, 0.4f, 0.f); //@diff(color_range)
    c2 = color(0.f, 0.4f, 0.6f); //@diff(color_range)

    noLoop();
}

void draw() {
    // Background
    setGradient(0, 0, width / 2, height, b1, b2, X_AXIS);
    setGradient(width / 2, 0, width / 2, height, b2, b1, X_AXIS);
    // Foreground
    setGradient(50, 90, 540, 80, c1, c2, Y_AXIS);
    setGradient(50, 190, 540, 80, c2, c1, X_AXIS);
}

void setGradient(int x, int y, float w, float h, uint32_t c1, uint32_t c2, int axis) {

    noFill();

    if (axis == Y_AXIS) { // Top to bottom gradient
        for (int i = y; i <= y + h; i++) {
            float    inter = map(i, y, y + h, 0, 1);
            uint32_t c     = lerpColor(c1, c2, inter);
            stroke_color(c);
            line(x, i, x + w, i);
        }
    } else if (axis == X_AXIS) { // Left to right gradient
        for (int i = x; i <= x + w; i++) {
            float    inter = map(i, x, x + w, 0, 1);
            uint32_t c     = lerpColor(c1, c2, inter);
            stroke_color(c);
            line(i, y, i, y + h);
        }
    }
}
