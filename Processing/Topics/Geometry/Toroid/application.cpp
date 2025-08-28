/**
 * Interactive Toroid
 * by Ira Greenberg. 
 * 
 * Illustrates the geometric relationship between Toroid, Sphere, and Helix
 * 3D primitives, as well as lathing principal.
 * 
 * Instructions: <br />
 * UP arrow key pts++ <br />
 * DOWN arrow key pts-- <br />
 * LEFT arrow key segments-- <br />
 * RIGHT arrow key segments++ <br />
 * 'a' key toroid radius-- <br />
 * 's' key toroid radius++ <br />
 * 'z' key initial polygon radius-- <br />
 * 'x' key initial polygon radius++ <br />
 * 'w' key toggle wireframe/solid shading <br />
 * 'h' key toggle sphere/helix <br />
 */
#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

int   pts    = 40;
float angle  = 0;
float radius = 60.0;

// lathe segments
int   segments    = 60;
float latheAngle  = 0;
float latheRadius = 100.0;

//vertices
std::vector<PVector> vertices, vertices2; //@diff(std::vector)

// for shaded or wireframe rendering
bool isWireFrame = false; //@diff(generic_type)

// for optional helix
bool  isHelix     = false; //@diff(generic_type)
float helixOffset = 5.0;


void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
}

void draw() {
    background(0.20f, 0.25f, 0.16f);
    // basic lighting setup
    lights(); //FIXME: lights() turns the shape color into grey
    // 2 rendering styles
    // wireframe or solid
    if (isWireFrame) {
        stroke(1.0f, 1.0f, 0.59f);
        noFill();
    } else {
        noStroke();
        fill(0.59f, 0.76f, 0.49f);
    }
    //center and spin toroid
    translate(width / 2, height / 2, -100);

    rotateX(frameCount * PI / 150);
    rotateY(frameCount * PI / 170);
    rotateZ(frameCount * PI / 90);

    // initialize point arrays
    vertices  = std::vector<PVector>(pts + 1); //@diff(std::vector)
    vertices2 = std::vector<PVector>(pts + 1); //@diff(std::vector)

    // fill arrays
    for (int i = 0; i <= pts; i++) {
        vertices[i]   = PVector();
        vertices2[i]  = PVector();
        vertices[i].x = latheRadius + sin(radians(angle)) * radius;
        if (isHelix) {
            vertices[i].z = cos(radians(angle)) * radius - (helixOffset *
                                                            segments) /
                                                               2;
        } else {
            vertices[i].z = cos(radians(angle)) * radius;
        }
        angle += 360.0 / pts;
    }

    // draw toroid
    latheAngle = 0;
    for (int i = 0; i <= segments; i++) {
        beginShape(QUAD_STRIP);
        for (int j = 0; j <= pts; j++) {
            if (i > 0) {
                vertex(vertices2[j].x, vertices2[j].y, vertices2[j].z);
            }
            vertices2[j].x = cos(radians(latheAngle)) * vertices[j].x;
            vertices2[j].y = sin(radians(latheAngle)) * vertices[j].x;
            vertices2[j].z = vertices[j].z;
            // optional helix offset
            if (isHelix) {
                vertices[j].z += helixOffset;
            }
            vertex(vertices2[j].x, vertices2[j].y, vertices2[j].z);
        }
        // create extra rotation for helix
        if (isHelix) {
            latheAngle += 720.0 / segments;
        } else {
            latheAngle += 360.0 / segments;
        }
        endShape();
    }
}

/*
 left/right arrow keys control ellipse detail
 up/down arrow keys control segment detail.
 'a','s' keys control lathe radius
 'z','x' keys control ellipse radius
 'w' key toggles between wireframe and solid
 'h' key toggles between toroid and helix
 */
void keyPressed() {
    // pts
    if (key == SDLK_UP) { //note: Arrow key handling using SDL named constants
        if (pts < 40) {
            pts++;
        }
    } else if (key == SDLK_DOWN) {
        if (pts > 3) {
            pts--;
        }
    }
    // extrusion length
    if (key == SDLK_LEFT) {
        if (segments > 3) {
            segments--;
        }
    } else if (key == SDLK_RIGHT) {
        if (segments < 80) {
            segments++;
        }
    }

    // lathe radius
    if (key == 'a') {
        if (latheRadius > 0) {
            latheRadius--;
        }
    } else if (key == 's') {
        latheRadius++;
    }
    // ellipse radius
    if (key == 'z') {
        if (radius > 10) {
            radius--;
        }
    } else if (key == 'x') {
        radius++;
    }
    // wireframe
    if (key == 'w') {
        if (isWireFrame) {
            isWireFrame = false;
        } else {
            isWireFrame = true;
        }
    }
    // helix
    if (key == 'h') {
        if (isHelix) {
            isHelix = false;
        } else {
            isHelix = true;
        }
    }
}
