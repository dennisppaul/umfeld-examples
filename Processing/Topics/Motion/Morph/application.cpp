/**
 * Morph. 
 * 
 * Changing one shape into another by interpolating
 * vertices from one to another
 */

#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

// Two std::vector to store the vertices for two shapes
// This example assumes that each shape will have the same
// number of vertices, i.e. the size of each vector will be the same
std::vector<PVector> myCircle;
std::vector<PVector> mySquare;

// An std::vector for a third set of vertices, the ones we will be drawing
// in the window
std::vector<PVector> morph;

// This boolean variable will control if we are morphing to a circle or square
bool state = false;

void settings() {
    size(640, 360);
}

void setup() {
    // Create a circle using vectors pointing from center
    for (int angle = 0; angle < 360; angle += 9) {
        // Note we are not starting from 0 in order to match the
        // path of a circle.
        PVector v = PVector::fromAngle(radians(angle - 135));
        v.mult(100);
        myCircle.push_back(v);
        // Let's fill out morph vector with blank PVectors while we are at it
        morph.push_back(PVector());
    }

    // A square is a bunch of vertices along straight lines
    // Top of square
    for (int x = -50; x < 50; x += 10) {
        mySquare.push_back(PVector(x, -50));
    }
    // Right side
    for (int y = -50; y < 50; y += 10) {
        mySquare.push_back(PVector(50, y));
    }
    // Bottom
    for (int x = 50; x > -50; x -= 10) {
        mySquare.push_back(PVector(x, 50));
    }
    // Left side
    for (int y = 50; y > -50; y -= 10) {
        mySquare.push_back(PVector(-50, y));
    }
}

void draw() {
    background(.2f); //@diff(color_range)

    // We will keep how far the vertices are from their target
    float totalDistance = 0;

    // Look at each vertex
    for (int i = 0; i < myCircle.size(); i++) {
        umfeld::PVector v1;
        // Are we lerping to the circle or square?
        if (state) {
            v1 = myCircle[i];
        } else {
            v1 = mySquare[i];
        }
        // Get the vertex we will draw
        PVector& v2 = morph[i]; //@diff(reference)
        // Lerp to the target
        v2.lerp(v1, 0.1);
        // Check how far we are from target
        totalDistance += PVector::dist(v1, v2);
    }

    // If all the vertices are close, switch shape
    if (totalDistance < 0.1) {
        state = !state;
    }

    // Draw relative to center
    translate(width / 2, height / 2);
    strokeWeight(4);
    // Draw a polygon that makes up all the vertices
    beginShape();
    noFill();
    stroke(1.f); //@diff(color_range)
    for (PVector v: morph) {
        vertex(v.x, v.y);
    }
    endShape(CLOSE);
}
