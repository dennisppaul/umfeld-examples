#pragma once
#include "Shape3D.h"
#include "PVector.h"

class Icosahedron : public Shape3D {
public:
    // icosahedron
    PVector topPoint;
    std::vector<PVector> topPent;
    PVector bottomPoint;
    std::vector<PVector> bottomPent;
    float angle = 0, radius = 150;
    float triDist;
    float triHt;
    float a, b, c;

    // default constructor
    Icosahedron() {
        init();
    }

    // constructor
    Icosahedron(float radius) {
        this->radius = radius; //@diff(pointer)
        init();
    }

    Icosahedron(PVector v, float radius) : Shape3D(v) {
        this->radius = radius;
        init();
    }

    // calculate geometry
    void init() {
        topPent.resize(5);
        bottomPent.resize(5);

        c = dist(cos(0) * radius, sin(0) * radius, cos(radians(72)) * radius, sin(radians(72)) * radius);
        b = radius;
        a = (float) (sqrt(((c * c) - (b * b))));

        triHt = (float) (sqrt((c * c) - ((c / 2) * (c / 2))));

        for (int i = 0; i < this->topPent.size(); i++) {
            this->topPent[i].set(cos(angle) * radius, sin(angle) * radius, triHt / 2.0f);
            angle += radians(72);
        }
        this->topPoint.set(0, 0, triHt / 2.0f + a);
        angle    = 72.0f / 2.0f;
        for (int i = 0; i < this->topPent.size(); i++) {
            this->bottomPent[i].set(cos(angle) * radius, sin(angle) * radius, -triHt / 2.0f);
            angle += radians(72);
        }
        this->bottomPoint.set(0, 0, -(triHt / 2.0f + a));
    }

    // draws icosahedron
    void create() {
        for (int i = 0; i < this->topPent.size(); i++) {
            // icosahedron top
            beginShape(TRIANGLES);
            if (i < this->topPent.size() - 1) {
                vertex(x + this->topPent[i].x, y + this->topPent[i].y, z + this->topPent[i].z);
                vertex(x + this->topPoint.x, y + this->topPoint.y, z + this->topPoint.z);
                vertex(x + this->topPent[i + 1].x, y + this->topPent[i + 1].y, z + this->topPent[i + 1].z);
            } else {
                vertex(x + this->topPent[i].x, y + this->topPent[i].y, z + this->topPent[i].z);
                vertex(x + this->topPoint.x, y + this->topPoint.y, z + this->topPoint.z);
                vertex(x + this->topPent[0].x, y + this->topPent[0].y, z + this->topPent[0].z);
            }
            endShape();

            // icosahedron bottom (reverse winding for downward faces)
            beginShape(TRIANGLES);
            if (i < this->bottomPent.size() - 1) {
                vertex(x + this->bottomPent[i].x, y + this->bottomPent[i].y, z + this->bottomPent[i].z);
                vertex(x + bottomPent[i + 1].x, y + bottomPent[i + 1].y, z + bottomPent[i + 1].z);
                vertex(x + bottomPoint.x, y + bottomPoint.y, z + bottomPoint.z);
            } else {
                vertex(x + this->bottomPent[i].x, y + this->bottomPent[i].y, z + this->bottomPent[i].z);
                vertex(x + this->bottomPent[0].x, y + this->bottomPent[0].y, z + this->bottomPent[0].z);
                vertex(x + this->bottomPoint.x, y + this->bottomPoint.y, z + this->bottomPoint.z);
            }
            endShape();
        }

        // icosahedron body
        for (int i = 0; i < this->topPent.size(); i++) {
            if (i < this->topPent.size() - 2) {
                beginShape(TRIANGLES);
                vertex(x + this->topPent[i].x, y + this->topPent[i].y, z + this->topPent[i].z);
                vertex(x + this->bottomPent[i + 1].x, y + this->bottomPent[i + 1].y, z + this->bottomPent[i + 1].z);
                vertex(x + this->bottomPent[i + 2].x, y + this->bottomPent[i + 2].y, z + this->bottomPent[i + 2].z);
                endShape();

                beginShape(TRIANGLES);
                vertex(x + this->bottomPent[i + 2].x, y + this->bottomPent[i + 2].y, z + this->bottomPent[i + 2].z);
                vertex(x + this->topPent[i].x, y + this->topPent[i].y, z + this->topPent[i].z);
                vertex(x + this->topPent[i + 1].x, y + this->topPent[i + 1].y, z + this->topPent[i + 1].z);
                endShape();
            } else if (i == this->topPent.size() - 2) {
                beginShape(TRIANGLES);
                vertex(x + this->topPent[i].x, y + this->topPent[i].y, z + this->topPent[i].z);
                vertex(x + this->bottomPent[i + 1].x, y + this->bottomPent[i + 1].y, z + this->bottomPent[i + 1].z);
                vertex(x + this->bottomPent[0].x, y + this->bottomPent[0].y, z + this->bottomPent[0].z);
                endShape();

                beginShape(TRIANGLES);
                vertex(x + this->bottomPent[0].x, y + this->bottomPent[0].y, z + this->bottomPent[0].z);
                vertex(x + this->topPent[i].x, y + this->topPent[i].y, z + this->topPent[i].z);
                vertex(x + this->topPent[i + 1].x, y + this->topPent[i + 1].y, z + this->topPent[i + 1].z);
                endShape();
            } else if (i == this->topPent.size() - 1) {
                beginShape(TRIANGLES);
                vertex(x + this->topPent[i].x, y + this->topPent[i].y, z + this->topPent[i].z);
                vertex(x + this->bottomPent[0].x, y + this->bottomPent[0].y, z + this->bottomPent[0].z);
                vertex(x + this->bottomPent[1].x, y + this->bottomPent[1].y, z + this->bottomPent[1].z);
                endShape();

                beginShape(TRIANGLES);
                vertex(x + this->bottomPent[1].x, y + this->bottomPent[1].y, z + this->bottomPent[1].z);
                vertex(x + this->topPent[i].x, y + this->topPent[i].y, z + this->topPent[i].z);
                vertex(x + this->topPent[0].x, y + this->topPent[0].y, z + this->topPent[0].z);
                endShape();
            }
        }
    }

    // overrided methods fom Shape3D
    void rotZ(float theta) {
        float tx = 0, ty = 0, tz = 0;
        // top point
        tx         = cos(theta) * topPoint.x + sin(theta) * topPoint.y;
        ty         = sin(theta) * topPoint.x - cos(theta) * topPoint.y;
        topPoint.x = tx;
        topPoint.y = ty;

        // bottom point
        tx            = cos(theta) * bottomPoint.x + sin(theta) * bottomPoint.y;
        ty            = sin(theta) * bottomPoint.x - cos(theta) * bottomPoint.y;
        bottomPoint.x = tx;
        bottomPoint.y = ty;

        // top and bottom pentagons
        for (int i = 0; i < this->topPent.size(); i++) {
            tx           = cos(theta) * this->topPent[i].x + sin(theta) * this->topPent[i].y;
            ty           = sin(theta) * this->topPent[i].x - cos(theta) * this->topPent[i].y;
            this->topPent[i].x = tx;
            this->topPent[i].y = ty;

            tx              = cos(theta) * this->bottomPent[i].x + sin(theta) * this->bottomPent[i].y;
            ty              = sin(theta) * this->bottomPent[i].x - cos(theta) * this->bottomPent[i].y;
            this->bottomPent[i].x = tx;
            this->bottomPent[i].y = ty;
        }
    }

    void rotX(float theta) {
    }

    void rotY(float theta) {
    }
};
