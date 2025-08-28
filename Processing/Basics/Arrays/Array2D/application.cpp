/**
 * Array 2D. 
 * 
 * Demonstrates the syntax for creating a two-dimensional (2D) array.
 * Values in a 2D array are accessed through two index values.  
 * 2D arrays are useful for storing images. In this example, each dot 
 * is colored in relation to its distance from the center of the image. 
 */
#include "Umfeld.h"

using namespace umfeld;

std::vector<std::vector<float>> distances; //@diff(std::vector)
float maxDistance;
int spacer;

void settings() {
    size(640, 360);
}

void setup() {
    maxDistance = dist(width / 2.f, height / 2.f, width, height);
    distances   = std::vector<std::vector<float>>(width, std::vector<float>(height)); //@diff(std::vector)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float distance  = dist(width / 2.f, height / 2.f, (float) x, (float) y);
            distances[x][y] = distance / maxDistance; //@diff(color_range)
            std::cout << (( distances[x][y])) << " ";
        }
    }
    std::cout << std::endl;
    spacer = 10;
    strokeWeight(6); //FIXME: doesn't change the point size
    noLoop(); // Run once and stop
}

void draw() {
    background(0.f);

    background(0.f);
    // This embedded loop skips over values in the arrays based on
    // the spacer variable, so there are more values in the array
    // than are drawn here. Change the value of the spacer variable
    // to change the density of the points
    for (int y = 0; y < height; y += spacer) {
        for (int x = 0; x < width; x += spacer) {
            stroke(distances[x][y]);
            point(x + spacer / 2, y + spacer / 2);
        }
    }
}
