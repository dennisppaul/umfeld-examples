/**
 * LoadFile 2
 * 
 * This example loads a data file about cars. Each element is separated
 * with a tab and corresponds to a different aspect of each car. The file stores 
 * the miles per gallon, cylinders, displacement, etc., for more than 400 different
 * makes and models. Press a mouse button to advance to the next group of entries.
 */
#include "Umfeld.h"
#include "Record.h"

using namespace umfeld;

std::vector<Record> records; //@diff(std::vector)
std::vector<std::string> lines; //@diff(std::vector)
int   recordCount;
PFont* body; //@diff(pointer)
int   num           = 9; // Display this many entries on each screen.
int   startingEntry = 0; // Display from this entry number


void settings() {
    size(640, 360);
}

void setup() {
    fill(1.f); //@diff(color_range)
    noLoop();

    // body = loadFont("TheSans-Plain-12.vlw", 12); // .vlw unsupported
    body = loadFont("SourceCodePro-Regular.ttf", 12);
    textFont(body);
    textSize(20);

    lines   = loadStrings("cars2.tsv");
    records.resize(lines.size()); //@diff(std::vector)
    for (int i = 0; i < lines.size(); i++) {
        std::vector<std::string> pieces = split(lines[i], "\t"); // Load data into array
        if (pieces.size() == 9) {
            records[recordCount] = Record(pieces);
            recordCount++;
        }
    }
    if (recordCount != records.size()) {
        records = std::vector<Record>(records.begin(), records.begin() + recordCount);
    }
}

void draw() {
    background(0.f); //@diff(color_range)
    for (int i = 0; i < num; i++) {
        int thisEntry = startingEntry + i;
        if (thisEntry < recordCount) {
            text(to_string(thisEntry) + " > " + records[thisEntry].name, 20, 20 + i * 20); //@diff(data_conversion)
        }
    }
}

void mousePressed() {
    startingEntry += num;
    if (startingEntry > records.size()) {
        startingEntry = 0; // go back to the beginning
    }
    redraw();
}
/*
note:
- segfaults happens when trying to load unsupported fonts like .vlw
- might need to guard against unsupported font formats
*/