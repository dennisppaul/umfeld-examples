/**
 * IntList Lottery example
 * 
 * This examples demonstrates the use of std::vector.
 * The counterpart of this Processing example demonstrates the IntList which is 
 * part of the Processing core library. Here, we replace it with the 
 * std::vector, which is a container provided by the c++ STL library.
 * 
 * In this example, three lists of integers are created.  One is a pool of numbers
 * that is shuffled and picked randomly from.  One is the list of "picked" numbers.
 * And one is a lottery "ticket" which includes 5 numbers that are trying to be matched.
 */
#include "Umfeld.h"
#include <random>

using namespace umfeld;

// Three lists of integers
std::vector<int> lottery;
std::vector<int> results;
std::vector<int> ticket;

void showList(std::vector<int> list, float x, float y); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}


void setup() {
    set_frame_rate(30); //@diff(frameRate)
    
    // Load font for text rendering
    PFont* font = loadFont("SourceCodePro-Regular.ttf", 12);
    textFont(font);
    textFont(font); // Set the font for text rendering

    // Add 20 integers in order to the lottery list
    for (int i = 0; i < 20; i++) {
        // push_back() is a method that adds an element to the end of the vector
        // Processing: similar to append()
        lottery.push_back(i); //@diff(std::vector)
    }

    // Pick five numbers from the lottery list to go into the Ticket list
    for (int i = 0; i < 5; i++) {
        int index = int(random(lottery.size()));
        ticket.push_back(lottery[index]);
    }
}

void draw() {
    background(.2f); //@diff(color_range)

    // The shuffle() method randomly shuffles the order of the values in the list
    // the std::shuffle() requires a random number generator
    // Here we use std::default_random_engine to create a random number generator (requires the #include <random> header above)
    std::shuffle(lottery.begin(), lottery.end(), std::default_random_engine());

    // Call a method that will display the integers in the list at an x,y location
    showList(lottery, 16, 48);
    showList(results, 16, 100);
    showList(ticket, 16, 140);


    // This loop checks if the picked numbers (results)
    // match the ticket numbers
    for (int i = 0; i < results.size(); i++) {
        // Are the integers equal?
        if (results[i] == ticket[i]) {
            fill(0.f, 1.f, 0.f, .4f); // if so green
        } else {
            fill(1.f, 0.f, 0.f, .4f); // if not red
        }
        ellipse(16 + i * 32, 140, 24, 24);
    }


    // One every 30 frames we pick a new lottery number to go in results
    if (frameCount % 30 == 0) {
        if (results.size() < 5) {
            // Get the first value in the lottery list and remove it
            // To remove an element from a vector, we can use the erase() method
            // This will remove the first element in the vector
            // To remove the Nth element, we can use lottery.erase(lottery.begin() + N);
            // To remove the last element, we can use lottery.pop_back();
            int val = lottery[0];
            lottery.erase(lottery.begin());
            // Put it in the results
            results.push_back(val);
        } else {
            // Ok we picked five numbers, let's reset
            for (int i = 0; i < results.size(); i++) {
                // Put the picked results back into the lottery
                lottery.push_back(results[i]);
            }
            // Clear the results and start over
            results.clear();
        }
    }
}

// Draw a list of numbers starting at an x,y location
void showList(std::vector<int> list, float x, float y) {
    for (int i = 0; i < list.size(); i++) {
        // Use the [] operator to pull a value from the list at the specified index
        int val = list[i];
        stroke(1.f); //@diff(stroke_color)
        noFill();
        ellipse(x + i * 32, y, 24, 24);
        
        fill(1.f); //@diff(fill_color)
        textAlign(CENTER);
        text(to_string(val), x + i * 32, y + 6);
    }
}
