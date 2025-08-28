#pragma once
#include "Umfeld.h"

using namespace umfeld;

class CA {
public:
    std::vector<int> cells;      // An array of 0s and 1s  //@diff(std::vector)
    int              generation; // How many generations?
    int              scl;        // How many pixels wide/high is each cell?

    std::vector<int> rules; // Array to store the rules, for example {0,1,1,0,1,1,0,1} //@diff(std::vector)

    // Default constructor
    CA() {
        rules = {0, 1, 0, 1, 1, 0, 1, 0}; // Default ruleset
        scl   = 1; // Default scale
        cells.resize(width / scl); //@diff(std::vector)
        restart();
    }
    CA(std::vector<int> r) {
        rules = r;
        scl   = 1;
        cells.resize(width / scl); //@diff(std::vector)
        restart();
    }

    // Set the rules of the CA
    void setRules(std::vector<int> r) { //@diff(std::vector)
        rules = r;
    }

    // Make a random ruleset
    void randomize() {
        for (int i = 0; i < 8; i++) {
            rules[i] = int(random(2));
        }
    }

    // Reset to generation 0
    void restart() {
        for (int i = 0; i < cells.size(); i++) {
            cells[i] = 0;
        }
        // We arbitrarily start with just the middle
        // cell having a state of "1"
        cells[cells.size() / 2] = 1;
        generation              = 0;
    }

    // The process of creating the new generation
    void generate() {
        // First we create an empty array for the new values
        std::vector<int> nextgen(cells.size()); //@diff(std::vector)
        // For every spot, determine new state by examing current
        // state, and neighbor states
        // Ignore edges that only have one neighor
        for (int i = 1; i < cells.size() - 1; i++) { //@diff(std::vector)
            int left  = cells[i - 1]; // Left neighbor state
            int me    = cells[i];     // Current state
            int right = cells[i + 1]; // Right neighbor state
            // Compute next generation state based on ruleset
            nextgen[i] = executeRules(left, me, right);
        }
        // Copy the array into current value
        for (int i = 1; i < cells.size() - 1; i++) {
            cells[i] = nextgen[i];
        }
        //cells = (int[]) nextgen.clone();
        generation++;
    }

    // This is the easy part, just draw the cells,
    // fill 255 for '1', fill 0 for '0'
    void render() {
        for (int i = 0; i < cells.size(); i++) {
            if (cells[i] == 1) {
                fill(1.f); //@diff(color_range)
            } else {
                fill(0.f); //@diff(color_range)
            }
            noStroke();
            rect(i * scl, generation * scl, scl, scl);
        }
    }

    // Implementing the Wolfram rules
    // Could be improved and made more concise,
    // but here we can explicitly see what is going on for each case
    int executeRules(int a, int b, int c) {
        if (a == 1 && b == 1 && c == 1) { return rules[0]; }
        if (a == 1 && b == 1 && c == 0) { return rules[1]; }
        if (a == 1 && b == 0 && c == 1) { return rules[2]; }
        if (a == 1 && b == 0 && c == 0) { return rules[3]; }
        if (a == 0 && b == 1 && c == 1) { return rules[4]; }
        if (a == 0 && b == 1 && c == 0) { return rules[5]; }
        if (a == 0 && b == 0 && c == 1) { return rules[6]; }
        if (a == 0 && b == 0 && c == 0) { return rules[7]; }
        return 0;
    }

    // The CA is done if it reaches the bottom of the screen
    bool finished() { //@diff(generic_type)
        if ((float)generation > height / scl) {
            return true;
        } else {
            return false;
        }
    }
};
