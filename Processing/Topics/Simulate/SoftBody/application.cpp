/**
 * Soft Body 
 * by Ira Greenberg.  
 * 
 * Softbody dynamics simulation using curveVertex() and curveTightness().
 */

#include "Umfeld.h"

using namespace umfeld;

// center point
float centerX = 0, centerY = 0;

float radius = 45, rotAngle = -90;
float accelX, accelY;
float springing = .0009, damping = .98;

//corner nodes
int nodes = 5;
std::vector<float> nodeStartX(nodes);
std::vector<float> nodeStartY(nodes);
std::vector<float> nodeX(nodes);
std::vector<float> nodeY(nodes);
std::vector<float> angle(nodes);
std::vector<float> frequency(nodes);

// soft-body dynamics
float organicConstant = 1;

void moveShape(); //@diff(forward_declaration)
void drawShape(); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    //center shape in window
    centerX = width / 2;
    centerY = height / 2;
    // iniitalize frequencies for corner nodes
    for (int i = 0; i < nodes; i++) {
        frequency[i] = random(5, 12);
    }
    noStroke();
    set_frame_rate(30); //@diff(frameRate)
}

void draw() {
    //fade background
    fill(0.f, .39f); //@diff(color_range)
    rect(0, 0, width, height);
    drawShape();
    moveShape();
}

void drawShape() {
    //  calculate node  starting positions
    for (int i = 0; i < nodes; i++) {
        nodeStartX[i] = centerX + cos(radians(rotAngle)) * radius;
        nodeStartY[i] = centerY + sin(radians(rotAngle)) * radius;
        rotAngle += 360.0 / nodes;
    }

    // draw polygon
    g->curveTightness(organicConstant);
    fill(1.f); //@diff(color_range)
    beginShape();
    for (int i = 0; i < nodes; i++) {
        // curveVertex(nodeX[i], nodeY[i]); //unimplemented
    }
    for (int i = 0; i < nodes - 1; i++) {
        // curveVertex(nodeX[i], nodeY[i]); //unimplemented
    }
    endShape(CLOSE);
}

void moveShape() {
    //move center point
    float deltaX = mouseX - centerX;
    float deltaY = mouseY - centerY;

    // create springing effect
    deltaX *= springing;
    deltaY *= springing;
    accelX += deltaX;
    accelY += deltaY;

    // move predator's center
    centerX += accelX;
    centerY += accelY;

    // slow down springing
    accelX *= damping;
    accelY *= damping;

    // change curve tightness
    organicConstant = 1 - ((abs(accelX) + abs(accelY)) * .1);

    //move nodes
    for (int i = 0; i < nodes; i++) {
        nodeX[i] = nodeStartX[i] + sin(radians(angle[i])) * (accelX * 2);
        nodeY[i] = nodeStartY[i] + sin(radians(angle[i])) * (accelY * 2);
        angle[i] += frequency[i];
    }
}