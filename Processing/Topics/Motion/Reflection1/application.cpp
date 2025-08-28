/**
 * Non-orthogonal Reflection 
 * by Ira Greenberg. 
 * 
 * Based on the equation (R = 2N(N*L)-L) where R is the 
 * reflection vector, N is the normal, and L is the incident
 * vector.
 */
#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

// Position of left hand side of floor
PVector base1;
// Position of right hand side of floor
PVector base2;
// Length of floor
float baseLength;

// An array of subpoints along the floor path
std::vector<PVector> coords; //@diff(std::vector)

// Variables related to moving ball
PVector position;
PVector velocity;
float   r     = 6;
float   speed = 3.5;

void createGround(); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    fill(.5f); //@diff(color_range)
    base1 = PVector(0, height - 150);
    base2 = PVector(width, height);
    createGround();

    // start ellipse at middle top of screen
    position = PVector(width / 2, 0);

    // calculate initial random velocity
    velocity = PVector::random2D();
    velocity.mult(speed);
}

void draw() {
    // draw background
    fill(0.f, .047f); //@diff(color_range)
    noStroke();
    rect(0, 0, width, height);

    // draw base
    fill(.78f); //@diff(color_range)
    quad(
        base1.x, base1.y, 0.f,
        base2.x, base2.y, 0.f,
        base2.x, height, 0.f,
        0.f, height, 0.f);

    // calculate base top normal
    PVector baseDelta = PVector::sub(base2, base1);
    baseDelta.normalize();
    PVector normal = PVector(-baseDelta.y, baseDelta.x);

    // draw ellipse
    noStroke();
    fill(1.f); //@diff(color_range)
    ellipse(position.x, position.y, r * 2, r * 2);

    // move elipse
    position.add(velocity);

    // normalized incidence vector
    PVector incidence = PVector::mult(velocity, -1);
    incidence.normalize();

    // detect and handle collision
    for (int i = 0; i < coords.size(); i++) {
        // check distance between ellipse and base top coordinates
        if (PVector::dist(position, coords[i]) < r) {

            // calculate dot product of incident vector and base top normal
            float dot = incidence.dot(normal);

            // calculate reflection vector
            // assign reflection vector to direction vector
            velocity.set(2 * normal.x * dot - incidence.x, 2 * normal.y * dot - incidence.y, 0);
            velocity.mult(speed);

            // draw base top normal at collision point
            stroke(1.f, .5f, 0.f); //@diff(color_range)
            line(position.x, position.y, position.x - normal.x * 100, position.y - normal.y * 100);
        }
    }

    // detect boundary collision
    // right
    if (position.x > width - r) {
        position.x = width - r;
        velocity.x *= -1;
    }
    // left
    if (position.x < r) {
        position.x = r;
        velocity.x *= -1;
    }
    // top
    if (position.y < r) {
        position.y = r;
        velocity.y *= -1;
        // randomize base top
        base1.y = random(height - 100, height);
        base2.y = random(height - 100, height);
        createGround();
    }
}


// Calculate variables for the ground
void createGround() {
    // calculate length of base top
    baseLength = PVector::dist(base1, base2);

    // fill base top coordinate array
    coords.resize(ceil(baseLength));
    for (int i = 0; i < coords.size(); i++) {
        coords[i]   = PVector();
        coords[i].x = base1.x + ((base2.x - base1.x) / baseLength) * i;
        coords[i].y = base1.y + ((base2.y - base1.y) / baseLength) * i;
    }
}

/*
note:
- trail artifacts issue
- umfeld uses GL_RGBA8 framebuffer causing 8-bit precision loss in alpha blending
- small alpha values (0.04) get quantized and don't fade to zero cleanly
- leaving gray residue
- suggestion: make api for setting the fbo to GL_RGBA32F or GL_RGBA16F
*/
