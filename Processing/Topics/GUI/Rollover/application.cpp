/**
 * Rollover. 
 * 
 * Roll over the colored squares in the center of the image
 * to change the color of the outside rectangle. 
 */


#include "Umfeld.h"

using namespace umfeld;

int rectX, rectY;     // Position of square button
int circleX, circleY; // Position of circle button
int rectSize   = 90;  // Diameter of rect
int circleSize = 93;  // Diameter of circle

uint32_t rectColor;   //@diff(color_type)
uint32_t circleColor; //@diff(color_type)
uint32_t baseColor;   //@diff(color_type)

bool rectOver   = false; //@diff(generic_type)
bool circleOver = false; //@diff(generic_type)

void update(int x, int y); //@diff(forward_declaration)
bool overRect(int x, int y, int width, int height); //@diff(forward_declaration)
bool overCircle(int x, int y, int diameter); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    rectColor   = color(0.f); //@diff(color_range)
    circleColor = color(1.f); //@diff(color_range)
    baseColor   = color(.4); //@diff(color_range)
    circleX     = width / 2.f + circleSize / 2.f + 10;
    circleY     = height / 2.f;
    rectX       = width / 2.f - rectSize - 10;
    rectY       = height / 2.f - rectSize / 2.f;
    ellipseMode(CENTER);
}

void draw() {
    update(mouseX, mouseY);

    noStroke();
    float r,g,b,a;
    if (rectOver) {
        color_unpack(rectColor, r, g, b, a);
        background(r,g,b,a);
    } else if (circleOver) {
        color_unpack(circleColor, r, g, b, a);
        background(r,g,b,a);
    } else {
        color_unpack(baseColor, r, g, b, a);
        background(r,g,b,a);
    }

    stroke(1.f); //@diff(color_range)
    fill_color_32(rectColor);
    rect(rectX, rectY, rectSize, rectSize);
    stroke(0.f); //@diff(color_range));
    fill_color_32(circleColor);
    ellipse(circleX, circleY, circleSize, circleSize);
}

void update(int x, int y) {
    if (overCircle(circleX, circleY, circleSize)) {
        circleOver = true;
        rectOver   = false;
    } else if (overRect(rectX, rectY, rectSize, rectSize)) {
        rectOver   = true;
        circleOver = false;
    } else {
        circleOver = rectOver = false;
    }
}

bool overRect(int x, int y, int width, int height) { //@diff(generic_type)
    if (mouseX >= x && mouseX <= x + width &&
        mouseY >= y && mouseY <= y + height) {
        return true;
    } else {
        return false;
    }
}

bool overCircle(int x, int y, int diameter) { //@diff(generic_type)
    float disX = x - mouseX;
    float disY = y - mouseY;
    if (sqrt(sq(disX) + sq(disY)) < diameter / 2) {
        return true;
    } else {
        return false;
    }
}
