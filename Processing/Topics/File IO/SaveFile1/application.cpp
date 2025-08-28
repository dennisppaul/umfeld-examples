/**
 * SaveFile 1
 * 
 * Saving files is a useful way to store data so it can be viewed after a 
 * program has stopped running. The saveStrings() function writes an array 
 * of strings to a file, with each string written to a new line. This file 
 * is saved to the sketch's folder.
 */

#include "Umfeld.h"

using namespace umfeld;

std::vector<int> x; //@diff(std::vector)
std::vector<int> y; //@diff(std::vector)

void settings() {
    size(640, 360);
}

void setup() {

}

void draw() {
    background(.8f); //@diff(color_range)
    stroke(0.f); //@diff(color_range)
    noFill();
    beginShape();
    for (int i = 0; i < x.size(); i++) {
        vertex(x[i], y[i]);
    }
    endShape();
    // Show the next segment to be added
    if (x.size() >= 1) {
        stroke(1.f); //@diff(color_range)
        line(mouseX, mouseY, x[x.size() - 1], y[x.size() - 1]);
    }
}

void mousePressed() { // Click to add a line segment
    x.push_back(mouseX);
    y.push_back(mouseY);
}

void keyPressed() { // Press a key to save the data
    std::vector<std::string> lines(x.size()); //@diff(std::vector)
    for (int i = 0; i < x.size(); i++) {
        lines[i] = std::to_string(x[i]) + "\t" + std::to_string(y[i]); //@diff(data_conversion)
    }
    saveStrings("lines.txt", lines);
    exit(); // Stop the program
}
