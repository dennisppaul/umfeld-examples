/**
 * Button. 
 * 
 * Click on one of the colored shapes in the 
 * center of the image to change the color of 
 * the background. 
 */
#include "Umfeld.h"

using namespace umfeld;

int     rectX, rectY;     // Position of square button
int     circleX, circleY; // Position of circle button
int     rectSize   = 90;  // Diameter of rect
int     circleSize = 93;  // Diameter of circle
uint32_t   rectColor, circleColor, baseColor; //@diff(color_type)
uint32_t   rectHighlight, circleHighlight;
uint32_t   currentColor;
bool rectOver   = false; //@diff(generic_type)
bool circleOver = false;

void update(int x, int y); //@diff(forward_declaration)
bool overRect(int x, int y, int width, int height); //@diff(forward_declaration)
bool overCircle(int x, int y, int diameter); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    rectColor       = color(0.f); //@diff(color_range)
    rectHighlight   = color(.2f); //@diff(color_range)
    circleColor     = color(1.f); //@diff(color_range)
    circleHighlight = color(.8f); //@diff(color_range)
    baseColor       = color(.4f); //@diff(color_range)
    currentColor    = baseColor;
    circleX         = width / 2.f + circleSize / 2.f + 10;
    circleY         = height / 2.f;
    rectX           = width / 2.f - rectSize - 10;
    rectY           = height / 2.f - rectSize / 2.f;
    ellipseMode(CENTER);
}

void draw() {
    update(mouseX, mouseY);
    float r,g,b,a;
    color_unpack(currentColor, r, g, b, a); //note: must be able to set background() color with uint32_t
    static bool printed=false;
    background(r,g,b,a);

    if (rectOver) {
        fill_color(rectHighlight);
    } else {
        fill_color(rectColor);
    }
    stroke(1.f); //@diff(color_range)
    rect(rectX, rectY, rectSize, rectSize);

    if (circleOver) {
        fill_color(circleHighlight);
    } else {
        fill_color(circleColor);
    }
    stroke(0.f); //@diff(color_range)
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

void mousePressed() {
    if (circleOver) {
        currentColor = circleColor;
    }
    if (rectOver) {
        currentColor = rectColor;
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