/**
 * LoadFile 1
 * 
 * Loads a text file that contains two numbers separated by a tab ('\t').
 * A new pair of numbers is loaded each frame and used to draw a point on the screen.
 */
#include "Umfeld.h"

using namespace umfeld;

std::vector<std::string> lines; //@diff(std::vector)
int idx = 0;

void settings() {
    size(640, 360);
}

void setup() {
    background(0.f); //@diff(color_range)
    stroke(1.f); //@diff(color_range)
    set_frame_rate(12); //@diff(frameRate)
    lines = loadStrings("positions.txt");
}

void draw() {
    if (idx < lines.size()) {
        std::vector<std::string> pieces = split(lines[idx], "\t"); //@diff(std::vector)
        if (pieces.size() == 2) {
            // Scale the coordinates to match the size of the sketch window
            float x = map(atof(pieces[0].data()), 0, 100, 0, width); //@diff(data_conversion)
            float y = map(atof(pieces[1].data()), 0, 100, 0, height); //@diff(data_conversion)
            point(x, y);
        }
        // Go to the next line for the next run through draw()
        idx = idx + 1;
    }
}
