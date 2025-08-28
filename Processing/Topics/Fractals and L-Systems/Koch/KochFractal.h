// Koch Curve
// A class to manage the list of line segments in the snowflake pattern

#pragma once
#include "Umfeld.h"
#include "PVector.h"
#include "KochLine.h"

using namespace umfeld;

class KochFractal {
public:
    PVector             start; // A PVector for the start
    PVector             end;   // A PVector for the end
    std::vector<KochLine> lines; // A list to keep track of all the lines //@diff(std::vector)
    int                 count;

    KochFractal() {
        lines = std::vector<KochLine>();
        // Will be initialized in setup
    }
    
    void init() {
        start.set(0, height - 20);
        end.set(width, height - 20);
        restart();
    }

    void nextLevel() {
        // For every line that is in the vector
        // create 4 more lines in a new vector
        lines = iterate(lines);
        count++;
    }

    void restart() {
        count = 0; // Reset count
        lines.clear(); // Empty the vector //@diff(std::vector)
        lines.push_back(KochLine(start, end)); // Add the initial line (from one end PVector to the other) //@diff(std::vector)
    }

    int getCount() {
        return count;
    }

    // This is easy, just draw all the lines
    void render() {
        for (KochLine l: lines) {
            l.display();
        }
    }

    // This is where the **MAGIC** happens
    // Step 1: Create an empty vector
    // Step 2: For every line currently in the vector
    //   - calculate 4 line segments based on Koch algorithm
    //   - add all 4 line segments into the new vector
    // Step 3: Return the new vector and it becomes the list of line segments for the structure

    // As we do this over and over again, each line gets broken into 4 lines, which gets broken into 4 lines, and so on. . .
    std::vector<KochLine> iterate(std::vector<KochLine> before) { //@diff(std::vector)
        std::vector<KochLine> now; // Create empty list
        for (KochLine l: before) {
            // Calculate 5 koch PVectors (done for us by the line object)
            PVector a = l.start();
            PVector b = l.kochleft();
            PVector c = l.kochmiddle();
            PVector d = l.kochright();
            PVector e = l.end();
            // Make line segments between all the PVectors and add them
            now.push_back(KochLine(a, b)); //@diff(std::vector)
            now.push_back(KochLine(b, c)); //@diff(std::vector)
            now.push_back(KochLine(c, d)); //@diff(std::vector)
            now.push_back(KochLine(d, e)); //@diff(std::vector)
        }
        return now;
    }
};
