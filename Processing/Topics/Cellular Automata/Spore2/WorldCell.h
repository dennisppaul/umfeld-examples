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
    uint32_t& spore1;
    uint32_t& spore2;
    uint32_t& spore3;
    uint32_t& spore4;

    Cell(int xin, int yin, World& world, uint32_t& s1, uint32_t& s2, uint32_t& s3, uint32_t& s4) :
        x(xin), y(yin), w(world), spore1(s1), spore2(s2), spore3(s3), spore4(s4) {}

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
        uint32_t black = color(0.f, 0.f, 0.f);
        // uint32_t black = 0x000000; // this is the same as above
        int myColor = w.getpix(x, y);
        if (myColor == spore1) {
            if (w.getpix(x - 1, y + 1) == black && w.getpix(x + 1, y + 1) == black && w.getpix(x, y + 1) == black) {
                move(0, 1);
            } else if (w.getpix(x - 1, y) == spore2 && w.getpix(x - 1, y - 1) != black) {
                move(0, -1);
            } else if (w.getpix(x - 1, y) == spore2 && w.getpix(x - 1, y - 1) == black) {
                move(-1, -1);
            } else if (w.getpix(x + 1, y) == spore1 && w.getpix(x + 1, y - 1) != black) {
                move(0, -1);
            } else if (w.getpix(x + 1, y) == spore1 && w.getpix(x + 1, y - 1) == black) {
                move(1, -1);
            } else {
                move((int) random(3) - 1, 0);
            }
        } else if (myColor == spore2) {
            if (w.getpix(x - 1, y + 1) == black && w.getpix(x + 1, y + 1) == black && w.getpix(x, y + 1) == black) {
                move(0, 1);
            } else if (w.getpix(x + 1, y) == spore1 && w.getpix(x + 1, y - 1) != black) {
                move(0, -1);
            } else if (w.getpix(x + 1, y) == spore1 && w.getpix(x + 1, y - 1) == black) {
                move(1, -1);
            } else if (w.getpix(x - 1, y) == spore2 && w.getpix(x - 1, y - 1) != black) {
                move(0, -1);
            } else if (w.getpix(x - 1, y) == spore2 && w.getpix(x - 1, y - 1) == black) {
                move(-1, -1);
            } else {
                move((int) random(3) - 1, 0);
            }
        } else if (myColor == spore3) {
            if (w.getpix(x - 1, y - 1) == black && w.getpix(x + 1, y - 1) == black && w.getpix(x, y - 1) == black) {
                move(0, -1);
            } else if (w.getpix(x - 1, y) == spore4 && w.getpix(x - 1, y + 1) != black) {
                move(0, 1);
            } else if (w.getpix(x - 1, y) == spore4 && w.getpix(x - 1, y + 1) == black) {
                move(-1, 1);
            } else if (w.getpix(x + 1, y) == spore3 && w.getpix(x + 1, y + 1) != black) {
                move(0, 1);
            } else if (w.getpix(x + 1, y) == spore3 && w.getpix(x + 1, y + 1) == black) {
                move(1, 1);
            } else {
                move((int) random(3) - 1, 0);
            }
        } else if (myColor == spore4) {
            if (w.getpix(x - 1, y - 1) == black && w.getpix(x + 1, y - 1) == black && w.getpix(x, y - 1) == black) {
                move(0, -1);
            } else if (w.getpix(x + 1, y) == spore3 && w.getpix(x + 1, y + 1) != black) {
                move(0, 1);
            } else if (w.getpix(x + 1, y) == spore3 && w.getpix(x + 1, y + 1) == black) {
                move(1, 1);
            } else if (w.getpix(x - 1, y) == spore4 && w.getpix(x - 1, y + 1) != black) {
                move(0, 1);
            } else if (w.getpix(x - 1, y) == spore4 && w.getpix(x - 1, y + 1) == black) {
                move(-1, 1);
            } else {
                move((int) random(3) - 1, 0);
            }
        }
    }

    // Will move the cell (dx, dy) units if that space is empty
    void move(int dx, int dy) {
        uint32_t black = color(0.f, 0.f, 0.f);
        if (w.getpix(x + dx, y + dy) == black) {
            w.setpix(x + dx, y + dy, w.getpix(x, y));
            w.setpix(x, y, black);
            x += dx;
            y += dy;
        }
    }
};

