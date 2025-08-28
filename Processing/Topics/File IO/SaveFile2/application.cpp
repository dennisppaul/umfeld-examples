/**
 * SaveFile 2
 * 
 * This example uses a std::ofstream object to write data continuously to a file
 * while the mouse is pressed. When a key is pressed, the file closes
 * itself and the program is stopped.
 */
#include "Umfeld.h"
#include <fstream>

using namespace umfeld;

std::ofstream output; //@diff(PrintWriter)

void settings() {
    size(640, 360);
}

void setup() {
    // Create a new file in the sketch directory
    output.open("positions.txt");
    set_frame_rate(12); //@diff(frameRate)
    stroke(1.f); //@diff(color_range)
}

void draw() {
    if (isMousePressed) {
        point(mouseX, mouseY);
        // check if the file is open before writing
        if (output.is_open()) {
            // Write the current mouse position to the file in c++ style
            output << mouseX << "\t" << mouseY << std::endl;
        }
    }
}

void keyPressed() { // Press a key to save the data
    if (output.is_open()) {
        output.flush(); // Write the remaining data
        output.close(); // Finish the file
    }
    exit(); // Stop the program
}