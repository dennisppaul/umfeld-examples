/**
 * Reach 3  
 * based on code from Keith Peters.
 * 
 * The arm follows the position of the ball by
 * calculating the angles with atan2().
 */
#include "Umfeld.h"

using namespace umfeld;

int numSegments = 8;
std::vector<float> x(numSegments); //@diff(std::vector)
std::vector<float> y(numSegments); //@diff(std::vector)
std::vector<float> angle(numSegments); //@diff(std::vector)
float segLength = 26;
float targetX, targetY;

float ballX          = 50;
float ballY          = 50;
int   ballXDirection = 1;
int   ballYDirection = -1;

void positionSegment(int a, int b); //@diff(forward_declaration)
void reachSegment(int i, float xin, float yin); //@diff(forward_declaration)
void segment(float x, float y, float a, float sw); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    strokeWeight(20.0);
    stroke(1.f, .39f); //@diff(color_range)
    noFill();
    ellipseDetail(36); // Ensure smooth circles
	//FIXME: enums for strokeJoin() and strokeCap() might need re-organization
    strokeJoin(ROUND); // Use round joins to avoid spikes at segment connections
    
    // hacky, but the ellipse stroke doesn't appear properly otherwise
    auto* pg = dynamic_cast<PGraphics*>(g);
    if (pg != nullptr) {
        pg->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);
    }
    
    x[x.size() - 1] = width / 2; // Set base x-coordinate
    y[x.size() - 1] = height;    // Set base y-coordinate
}

void draw() {
    background(0.f);

    strokeWeight(20);
    ballX = ballX + 1.0 * ballXDirection;
    ballY = ballY + 0.8 * ballYDirection;
    if (ballX > width - 25 || ballX < 25) {
        ballXDirection *= -1;
    }
    if (ballY > height - 25 || ballY < 25) {
        ballYDirection *= -1;
    }
    ellipse(ballX, ballY, 30, 30);

    reachSegment(0, ballX, ballY);
    for (int i = 1; i < numSegments; i++) {
        reachSegment(i, targetX, targetY);
    }
    for (int i = x.size() - 1; i >= 1; i--) {
        positionSegment(i, i - 1);
    }
    for (int i = 0; i < x.size(); i++) {
        segment(x[i], y[i], angle[i], (i + 1) * 2);
    }
}

void positionSegment(int a, int b) {
    x[b] = x[a] + cos(angle[a]) * segLength;
    y[b] = y[a] + sin(angle[a]) * segLength;
}

void reachSegment(int i, float xin, float yin) {
    float dx = xin - x[i];
    float dy = yin - y[i];
    angle[i] = atan2(dy, dx);
    targetX  = xin - cos(angle[i]) * segLength;
    targetY  = yin - sin(angle[i]) * segLength;
}

void segment(float x, float y, float a, float sw) {
    strokeWeight(sw);
    pushMatrix();
    translate(x, y);
    rotate(a);
    line(0, 0, segLength, 0);
    popMatrix();
}
/*
note:
- I see the stroke triangulation of the RENDER_MODE_BUFFERED is unimplemented yet. (inside src/PGraphicsOpenGL_3_3_core.cpp)
*/