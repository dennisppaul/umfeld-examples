/**
 * Pie Chart  
 * 
 * Uses the arc() function to generate a pie chart from the data
 * stored in an array. 
 */

#include "Umfeld.h"

using namespace umfeld;

std::vector<int> angles = {30, 10, 45, 35, 60, 38, 75, 67}; //@diff(std::vector)

void pieChart(float diameter, const std::vector<int>& data); //@diff(foward_declaration, std::vector, reference)

void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    noLoop(); // Run once and stop
}


void draw() {
    background(.4f);
    pieChart(300, angles);
}

void pieChart(float diameter, const std::vector<int>& data) {
    float lastAngle = 0;
    for (int i = 0; i < data.size(); i++) {
        float gray = map(i, 0, data.size(), 0.f, 1.f);
        fill(gray); //@diff(color_range)
        arc(width / 2, height / 2, diameter, diameter, lastAngle, lastAngle + radians(data[i]), PIE);
        lastAngle += radians(data[i]);
    }
}
