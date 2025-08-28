/**
 * Reach 2  
 * based on code from Keith Peters.
 * 
 * The arm follows the position of the mouse by
 * calculating the angles with atan2(). 
 */
#include "Umfeld.h"

using namespace umfeld;

int numSegments = 10;
std::vector<float> x(numSegments); //@diff(std::vector)
std::vector<float> y(numSegments); //@diff(std::vector)
std::vector<float> angle(numSegments); //@diff(std::vector)
float segLength = 26;
float targetX, targetY;

void positionSegment(int a, int b); //@diff(forward_declaration)
void reachSegment(int i, float xin, float yin); //@diff(forward_declaration)
void segment(float x, float y, float a, float sw); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    strokeWeight(20.0);
    stroke(1.f, .39f); //@diff(color_range)
    x[x.size() - 1] = width / 2; // Set base x-coordinate
    y[y.size() - 1] = height;    // Set base y-coordinate
    
    // FIXME: enable round stroke caps (but doesn't work, see note below)
    // strokeJoin(ROUND);
    strokeCap(ROUND);
}

void draw() {
    background(0.f); //@diff(color_range)

    reachSegment(0, mouseX, mouseY);
    for (int i = 1; i < numSegments; i++) {
        reachSegment(i, targetX, targetY);
    }
    for (int i = x.size() - 1; i >= 1; i--) {
        positionSegment(i, i - 1);
    }
    for (int i = 0; i < x.size(); i++) {
        segment(x[i], y[i], angle[i], (i + 1) * 2);
    }
}

void positionSegment(int a, int b) {
    x[b] = x[a] + cos(angle[a]) * segLength;
    y[b] = y[a] + sin(angle[a]) * segLength;
}

void reachSegment(int i, float xin, float yin) {
    float dx = xin - x[i];
    float dy = yin - y[i];
    angle[i] = atan2(dy, dx);
    targetX  = xin - cos(angle[i]) * segLength;
    targetY  = yin - sin(angle[i]) * segLength;
}

void segment(float x, float y, float a, float sw) {
    strokeWeight(sw);
    pushMatrix();
    translate(x, y);
    rotate(a);
    line(0, 0, segLength, 0);
    popMatrix();
}
/*
note: 
- the default stroke cap is angular/rectangle
- strokeCap() is implemented but the enum ROUND exist only for strokeJoint?
- the ROUND enum doesn't exist in the StrokeCap enum in UmfeldConstants.h 
- trying to add it causes naming conflict. maybe better to use namespace to scope them better, e.g STROKECAP::ROUND, STROKEJOINT::ROUND
- scoping also might help in some other places in umfeld, internally and externally.
- imho, the global naming conflict wont reslove otherwise
- also, the stroke render mode STROKE_RENDER_MODE_BARYCENTRIC_SHADER doesn't process the stroke caps.
- instead, the STROKE_RENDER_MODE_TRIANGULATE_2D shall be used.
*/