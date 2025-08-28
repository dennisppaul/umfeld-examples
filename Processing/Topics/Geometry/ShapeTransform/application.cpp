/**
 * Shape Transform
 * by Ira Greenberg.  
 * 
 * Illustrates the geometric relationship 
 * between Cube, Pyramid, Cone and 
 * Cylinder 3D primitives.
 * 
 * Instructions:
 * Up Arrow - increases points
 * Down Arrow - decreases points
 * 'p' key toggles between cube/pyramid
 */
#include "Umfeld.h"
#include "PVector.h"
// #include <SDL3/SDL_keycode.h>

using namespace umfeld;

int   pts            = 4;
float angle          = 0;
float radius         = 99;
float cylinderLength = 95;

//vertices
std::vector<std::vector<PVector>> vertices; //@diff(std::vector)
bool isPyramid = false; //@diff(generic_type)

float angleInc;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    noStroke();
    angleInc = PI / 300.0;
}

void draw() {
    background(0.66f, 0.37f, 0.37f); //@diff(color_range)
    lights();// FIXME: this turns the shape into gray
    fill(1.0f, 0.78f, 0.78f); //@diff(color_range)
    translate(width / 2, height / 2);
    rotateX(frameCount * angleInc);
    rotateY(frameCount * angleInc);
    rotateZ(frameCount * angleInc);

    // initialize vertex arrays
    vertices = std::vector<std::vector<PVector>>(2, std::vector<PVector>(pts + 1)); //@diff(std::vector)

    // fill arrays
    for (int i = 0; i < 2; i++) {
        angle = 0;
        for (int j = 0; j <= pts; j++) {
            vertices[i][j] = PVector();
            if (isPyramid) {
                if (i == 1) {
                    vertices[i][j].x = 0;
                    vertices[i][j].y = 0;
                } else {
                    vertices[i][j].x = cos(radians(angle)) * radius;
                    vertices[i][j].y = sin(radians(angle)) * radius;
                }
            } else {
                vertices[i][j].x = cos(radians(angle)) * radius;
                vertices[i][j].y = sin(radians(angle)) * radius;
            }
            vertices[i][j].z = cylinderLength;
            // the .0 after the 360 is critical
            angle += 360.0 / pts;
        }
        cylinderLength *= -1;
    }

    // draw cylinder tube
    beginShape(QUAD_STRIP);
    for (int j = 0; j <= pts; j++) {
        vertex(vertices[0][j].x, vertices[0][j].y, vertices[0][j].z);
        vertex(vertices[1][j].x, vertices[1][j].y, vertices[1][j].z);
    }
    endShape();

    //draw cylinder ends
    for (int i = 0; i < 2; i++) {
        beginShape();
        for (int j = 0; j < pts; j++) {
            vertex(vertices[i][j].x, vertices[i][j].y, vertices[i][j].z);
        }
        endShape(CLOSE);
    }
}


/*
 up/down arrow keys control
 polygon detail.
 */
void keyPressed() {
    if (key == SDLK_UP) { //note: Arrow key handling using SDL named constants
        if (pts < 90) {
            pts++;
        }
    } else if (key == SDLK_DOWN) {
        if (pts > 4) {
            pts--;
        }
    }
    if (key == 'p') {
        if (isPyramid) {
            isPyramid = false;
        } else {
            isPyramid = true;
        }
    }
}