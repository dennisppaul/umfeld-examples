/**
 * Bouncy Bubbles  
 * based on code from Keith Peters. 
 * 
 * Multiple-object collision.
 */

#include "Umfeld.h"
#include "Ball.h"

using namespace umfeld;


std::vector<Ball> balls(numBalls); //@diff(std::vector)

void settings() {
    size(640, 360);
}

void setup() {
    for (int i = 0; i < numBalls; i++) {
        balls[i] = Ball(random(width), random(height), random(30, 70), i, &balls);
    }
    noStroke();
    fill(1.f, .8f); //@diff(color_range)
}

void draw() {
    background(0.f); //@diff(color_range)
    for (Ball& ball: balls) { //@diff(range_based_for,reference)
        ball.collide();
        ball.move();
        ball.display();
    }
}

