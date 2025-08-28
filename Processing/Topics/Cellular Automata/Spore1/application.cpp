/**
 * Spore 1 
 * 
 * A short program for alife experiments. Click in the window to restart.
 * Each cell is represented by a pixel on the display as well as an entry in
 * the array 'cells'. Each cell has a run() method, which performs actions
 * based on the cell's surroundings.  Cells run one at a time (to avoid conflicts
 * like wanting to move to the same space) and in random order.
 */
#include "Umfeld.h"
#include "WorldCell.h"

using namespace umfeld;

World             w;
int               numcells = 0;
int               maxcells = 6700;
std::vector<Cell> cells;       //@diff(std::vector)
uint32_t          spore_color; //@diff(color_type)
// set lower for smoother animation, higher for faster simulation
int      runs_per_loop = 10000;
uint32_t black         = color(0.f, 0.f, 0.f);

void reset();       //@diff(forward_declaration)
void seed();        //@diff(forward_declaration)
void clearScreen(); //@diff(forward_declaration)


void settings() {
    size(640, 360);
}

void setup() {
    set_frame_rate(24); //@diff(frameRate)
    reset();
}

void reset() {
    clearScreen();
    w           = World();
    spore_color = color(.67f, 1.f, .5f); //@diff(color_range)
    cells.clear();
    seed();
}

void seed() {
    loadPixels();
    // Add cells at random places
    for (int i = 0; i < maxcells; i++) {
        int cX = (int) random(width);
        int cY = (int) random(height);
        if (w.getpix(cX, cY) == black) {
            w.setpix(cX, cY, spore_color);
            cells.emplace_back(cX, cY, w); //@diff(std::vector)
            numcells++;
        }
    }
    printf("Created %d cells, spore_color=%08x, black=%08x\n", numcells, spore_color, black);
    updatePixels();
}

void draw() {
    loadPixels();
    // Run cells in random order
    if (numcells > 0) {
        for (int i = 0; i < runs_per_loop; i++) {
            int selected = min((int) random(numcells), numcells - 1);
            cells[selected].run();
        }
    }
    updatePixels();
}

void clearScreen() {
    background(0.0f); //@diff(color_range)
}

void mousePressed() {
    numcells = 0;
    reset();
}
/*
note:
- the pixels array is not cleared. needs deeper inspection
*/