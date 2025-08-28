#pragma once
#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

class Word {
public:
    // Store a count for occurences in two different books
    int countDracula;
    int countFranken;
    // Also the total count
    int totalCount;

    // What is the String
    std::string word; //@diff(string)

    // Where is it on the screen
    PVector position;

    Word() : countDracula(0), countFranken(0), totalCount(0), word(""), position(PVector()) {}

    Word(std::string s) : countDracula(0), countFranken(0), totalCount(0) {
        position = PVector(random(width), random(-height, height * 2));
        word     = s;
    }

    // We will display a word if it appears at least 5 times
    // and only in one of the books
    bool qualify() { //@diff(generic_type)
        if ((countDracula == totalCount || countFranken == totalCount) && totalCount > 5) {
            return true;
        } else {
            return false;
        }
    }

    // Increment the count for Dracula
    void incrementDracula() {
        countDracula++;
        totalCount++;
    }


    // Increment the count for Frankenstein
    void incrementFranken() {
        countFranken++;
        totalCount++;
    }

    // The more often it appears, the faster it falls
    void move() {
        float speed = map(totalCount, 5, 25, 0.1, 0.4);
        speed       = constrain(speed, 0.f, 10.f);
        position.y += speed;

        if (position.y > height * 2) {
            position.y = -height;
        }
    }


    // Depending on which book it gets a color
    void display() {
        if (countDracula > 0) {
            fill(1.f); //@diff(color_range)
        } else if (countFranken > 0) {
            fill(0.f); //@diff(color_range)
        }
        // Its size is also tied to number of occurences
        float fs = map(totalCount, 5, 25, 2, 24);
        fs       = constrain(fs, 2.f, 48.f);
        textSize(fs);
        textAlign(CENTER);
        text(word, position.x, position.y);
    }
};
