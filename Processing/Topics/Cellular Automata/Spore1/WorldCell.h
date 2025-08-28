#pragma once
#include "Umfeld.h"

using namespace umfeld;

//  The World class simply provides two functions, get and set, which access the
//  display in the same way as getPixel and setPixel.  The only difference is that
//  the World class's get and set do screen wraparound ("toroidal coordinates").
class World {
public:
    void setpix(int x, int y, uint32_t c) {
        while (x < 0) {
            x += width;
        }
        while (x > width - 1) {
            x -= width;
        }
        while (y < 0) {
            y += height;
        }
        while (y > height - 1) {
            y -= height;
        }
        pixels[int((int)width * y + x)] = c; //@diff(set() unimplemented)
    }

    uint32_t getpix(int x, int y) {
        while (x < 0) {
            x += width;
        }
        while (x > width - 1) {
            x -= width;
        }
        while (y < 0) {
            y += height;
        }
        while (y > height - 1) {
            y -= height;
        }
        return pixels[int((int)width * y + x)]; //@diff(get() unimplemented)
    }
};

class Cell {
public:
    int x, y;
    World& w;
    Cell(int xin, int yin, World& world) : w(world) {
        x = xin;
        y = yin;
    }

    // Perform action based on surroundings
    void run() {
        // Fix cell coordinates
        while (x < 0) {
            x += width;
        }
        while (x > width - 1) {
            x -= width;
        }
        while (y < 0) {
            y += height;
        }
        while (y > height - 1) {
            y -= height;
        }
        
        // Cell instructions
        uint32_t black = color(0.f, 0.f, 0.f); //@diff(color_type)
        if (w.getpix(x + 1, y) == black) {
            move(0, 1);
        } else if (w.getpix(x, y - 1) != black && w.getpix(x, y + 1) != black) {
            move((int) random(3) - 1, (int) random(3) - 1);
        }
    }

    // Will move the cell (dx, dy) units if that space is empty
    void move(int dx, int dy) {
        uint32_t black = color(0.f, 0.f, 0.f); //@diff(color_type)
        if (w.getpix(x + dx, y + dy) == black) {
            w.setpix(x + dx, y + dy, w.getpix(x, y));
            w.setpix(x, y, black);
            x += dx;
            y += dy;
        }
    }
};
