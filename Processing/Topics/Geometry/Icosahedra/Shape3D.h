#pragma once
#include "Umfeld.h"
#include "PVector.h"
#include "Dimension3D.h"

using namespace umfeld;

class Shape3D {
public:
    float x, y, z;
    float w, h, d;

    Shape3D() {
    }

    Shape3D(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Shape3D(PVector p) {
        x = p.x;
        y = p.y;
        z = p.z;
    }


    Shape3D(Dimension3D dim) {
        w = dim.w;
        h = dim.h;
        d = dim.d;
    }

    Shape3D(float x, float y, float z, float w, float h, float d) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        this->h = h;
        this->d = d;
    }

    Shape3D(float x, float y, float z, Dimension3D dim) {
        this->x = x;
        this->y = y;
        this->z = z;
        w      = dim.w;
        h      = dim.h;
        d      = dim.d;
    }

    Shape3D(PVector p, Dimension3D dim) {
        x = p.x;
        y = p.y;
        z = p.z;
        w = dim.w;
        h = dim.h;
        d = dim.d;
    }

    void setLoc(PVector p) {
        x = p.x;
        y = p.y;
        z = p.z;
    }

    void setLoc(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }


    // override if you need these
    void rotX(float theta) {
    }

    void rotY(float theta) {
    }

    void rotZ(float theta) {
    }


    // must be implemented in subclasses
    virtual void init()   = 0;
    virtual void create() = 0;
    virtual ~Shape3D() = default;
};
