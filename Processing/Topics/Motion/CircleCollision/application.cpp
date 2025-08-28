/**
 * Circle Collision with Swapping Velocities
 * by Ira Greenberg. 
 * 
 * Based on Keith Peter's Solution in
 * Foundation Actionscript Animation: Making Things Move!
 */
#include "Umfeld.h"
#include "Ball.h"

using namespace umfeld;

std::vector<Ball> balls = {
    Ball(100, 400, 20),
    Ball(700, 400, 80)};

void settings() {
    size(640, 360);
}

void setup() {

}

void draw() {
    background(.2f); //@diff(color_range)

    for (Ball& b: balls) { //@diff(range_based_for,reference)
        b.update();
        b.display();
        b.checkBoundaryCollision();
    }

    balls[0].checkCollision(balls[1]);
}
