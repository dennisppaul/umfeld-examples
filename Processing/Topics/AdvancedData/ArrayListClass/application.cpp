/**
 * ArrayList of objects
 * by Daniel Shiffman.  
 * 
 * This example demonstrates how to use a Java ArrayList to store 
 * a variable number of objects.  Items can be added and removed
 * from the ArrayList.
 *
 * Click the mouse to add bouncing balls.
 */

#include "Umfeld.h"
#include "Ball.h"

using namespace umfeld;

std::vector<Ball> balls; //@diff(std::vector)
int ballWidth = 48;


void settings() {
    size(640, 360);
}

void setup() {
    noStroke();

    // Create an empty std::vector<Ball> (will store Ball objects)
    balls = std::vector<Ball>(); //@diff(std::vector)

    // Start by adding one element
    balls.push_back(Ball(width / 2, 0, ballWidth)); //@diff(std::vector)
}

void draw() {
    background(1.f); //@diff(color_range)

    // With a std::vector, we say balls.size()
    // The length of a std::vector is dynamic
    // Notice how we are looping through the std::vector backwards
    // This is because we are deleting elements from the list
    for (int i = balls.size() - 1; i >= 0; i--) {
        Ball& ball = balls[i]; //@diff(std::vector,reference)
        ball.move();
        ball.display();
        if (ball.finished()) {
            // Items can be deleted with erase()
            balls.erase(balls.begin() + i); //@diff(std::vector)
        }
    }
}

void mousePressed() {
    // A new ball object is added to the std::vector
    balls.push_back(Ball(mouseX, mouseY, ballWidth));
}
