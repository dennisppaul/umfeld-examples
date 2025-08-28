#pragma once
#include "Umfeld.h"

using namespace umfeld;

class Handle {
public:
    int     x, y;
    int     boxx, boxy;
    int     stretch;
    int     size;
    bool over; //@diff(generic_type)
    bool press;
    bool locked       = false;
    bool otherslocked = false;
    // Pointer to a vector of Handles to allow interaction with other handles
    // This allows the Handle to check if any other handle is locked
    // and prevent itself from being dragged if so.
    // This is necessary to ensure that handles can work together without conflicts.
    // In the Processing(java) version, this was implemented using a static array.
    // In C++, we use a pointer to a vector of Handles.
    // Without this being a pointer, every handle and the handles of the vector would be deep-copied, creating an infinite recursivity at the initialization of the handles.
    // On the Java side, the default copy operator(=) will do a shallow-copy, where it creates a reference implicitly.
    // In C++, we do it explicitly with a pointer, grabbing more control over the memory management.
    std::vector<Handle>* others; //@diff(std::vector, pointer)
    bool* firstMousePress;

    // Default constructor
    Handle() : firstMousePress(nullptr), others(nullptr), x(0), y(0), boxx(0), boxy(0), stretch(0), size(0), over(false), press(false), locked(false), otherslocked(false) {}

    Handle(bool& fmp) : firstMousePress(&fmp), others(nullptr), x(0), y(0), boxx(0), boxy(0), stretch(0), size(0), over(false), press(false), locked(false), otherslocked(false) {}

    Handle(int ix, int iy, int il, int is, std::vector<Handle>& o, bool& fmp) : firstMousePress(&fmp) {
        x       = ix;
        y       = iy;
        stretch = il;
        size    = is;
        boxx    = x + stretch - size / 2;
        boxy    = y - size / 2;
        others  = &o;
    }

    void update() {
        boxx = x + stretch;
        boxy = y - size / 2;

        if (others) {
            for (int i = 0; i < others->size(); i++) {
                if ((*others)[i].locked == true) {
                    otherslocked = true;
                    break;
                } else {
                    otherslocked = false;
                }
            }
        } else {
            otherslocked = false;
        }

        if (otherslocked == false) {
            overEvent();
            pressEvent();
        }

        if (press) {
            stretch = lock(mouseX - width / 2 - size / 2, 0, width / 2 - size - 1);
        }
    }

    void overEvent() {
        if (overRect(boxx, boxy, size, size)) {
            over = true;
        } else {
            over = false;
        }
    }

    void pressEvent() {
        if (over && firstMousePress && *firstMousePress || locked) {
            press  = true;
            locked = true;
        } else {
            press = false;
        }
    }

    void releaseEvent() {
        locked = false;
    }

    void display() {
        line(x, y, x + stretch, y);
        fill(1.f); //@diff(color_range)
        stroke(0.f); //@diff(color_range)
        rect(boxx, boxy, size, size);
        if (over || press) {
            line(boxx, boxy, boxx + size, boxy + size);
            line(boxx, boxy + size, boxx + size, boxy);
        }
    }
    bool overRect(int x, int y, int width, int height) {
        if (mouseX >= x && mouseX <= x + width &&
            mouseY >= y && mouseY <= y + height) {
            return true;
        } else {
            return false;
        }
    }
    int lock(int val, int minv, int maxv) {
        return min(max(val, minv), maxv);
    }
};
