#pragma once
#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

#define bounds 300.f

// Custom Cube Class

class Cube {
public:
    // Position, velocity vectors
    PVector position;
    PVector velocity;
    // Also using PVector to hold rotation values for 3 axes
    PVector rotation;

    // Vertices of the cube
    std::vector<PVector> vertices;
    // width, height, depth
    float w, h, d;

    // colors for faces of cube
    std::vector<uint32_t> quadBG;

    Cube() : w(0), h(0), d(0), vertices(24), quadBG(6),
        position(PVector()),
        velocity(PVector::random3D()),
        rotation(PVector(random(40, 100), random(40, 100), random(40, 100))) {
        // Initialize vertices to zero
        for (int i = 0; i < 24; i++) {
            vertices[i] = PVector();
        }
    }

    Cube(float w, float h, float d) : w(w), h(h), d(d), vertices(24), quadBG(6) {

        // Colors are hardcoded
        quadBG[0] = color(0.f); //@diff(color_range)
        quadBG[1] = color(.2f); //@diff(color_range)
        quadBG[2] = color(.4f); //@diff(color_range)
        quadBG[3] = color(.6f); //@diff(color_range)
        quadBG[4] = color(.8f); //@diff(color_range)
        quadBG[5] = color(1.f); //@diff(color_range)

        // Start in center
        position = PVector();
        // Random velocity vector
        velocity = PVector::random3D();
        // Random rotation
        rotation = PVector(random(40, 100), random(40, 100), random(40, 100));

        // cube composed of 6 quads
        //front
        vertices[0] = PVector(-w / 2, -h / 2, d / 2);
        vertices[1] = PVector(w / 2, -h / 2, d / 2);
        vertices[2] = PVector(w / 2, h / 2, d / 2);
        vertices[3] = PVector(-w / 2, h / 2, d / 2);
        //left
        vertices[4] = PVector(-w / 2, -h / 2, d / 2);
        vertices[5] = PVector(-w / 2, -h / 2, -d / 2);
        vertices[6] = PVector(-w / 2, h / 2, -d / 2);
        vertices[7] = PVector(-w / 2, h / 2, d / 2);
        //right
        vertices[8]  = PVector(w / 2, -h / 2, d / 2);
        vertices[9]  = PVector(w / 2, -h / 2, -d / 2);
        vertices[10] = PVector(w / 2, h / 2, -d / 2);
        vertices[11] =  PVector(w / 2, h / 2, d / 2);
        //back
        vertices[12] = PVector(-w / 2, -h / 2, -d / 2);
        vertices[13] = PVector(w / 2, -h / 2, -d / 2);
        vertices[14] = PVector(w / 2, h / 2, -d / 2);
        vertices[15] = PVector(-w / 2, h / 2, -d / 2);
        //top
        vertices[16] = PVector(-w / 2, -h / 2, d / 2);
        vertices[17] = PVector(-w / 2, -h / 2, -d / 2);
        vertices[18] = PVector(w / 2, -h / 2, -d / 2);
        vertices[19] = PVector(w / 2, -h / 2, d / 2);
        //bottom
        vertices[20] = PVector(-w / 2, h / 2, d / 2);
        vertices[21] = PVector(-w / 2, h / 2, -d / 2);
        vertices[22] = PVector(w / 2, h / 2, -d / 2);
        vertices[23] = PVector(w / 2, h / 2, d / 2);
    }

    // Cube shape itself
    void drawCube() {
        // Draw cube
        for (int i = 0; i < 6; i++) {
            fill_color_32(quadBG[i]);
            beginShape(QUADS);
            for (int j = 0; j < 4; j++) {
                vertex(vertices[j + 4 * i].x, vertices[j + 4 * i].y, vertices[j + 4 * i].z);
            }
            endShape();
        }
    }

    // Update location
    void update() {
        position.add(velocity);

        // Check wall collisions
        if (position.x > bounds / 2 || position.x < -bounds / 2) {
            velocity.x *= -1;
        }
        if (position.y > bounds / 2 || position.y < -bounds / 2) {
            velocity.y *= -1;
        }
        if (position.z > bounds / 2 || position.z < -bounds / 2) {
            velocity.z *= -1;
        }
    }


    // Display method
    void display() {
        pushMatrix();
        translate(position.x, position.y, position.z);
        rotateX(frameCount * PI / rotation.x);
        rotateY(frameCount * PI / rotation.y);
        rotateZ(frameCount * PI / rotation.z);
        noStroke();
        drawCube(); // Farm out shape to another method
        popMatrix();
    }
};
