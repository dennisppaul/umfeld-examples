/**
 * Spore 2 
 * by Mike Davis. 
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
int               maxcells = 8000;
int               numcells;
std::vector<Cell> cells; //@diff(std::vector)
uint32_t          spore1, spore2, spore3, spore4;
uint32_t          black = color(0.f, 0.f, 0.f); //@diff(color_range)
// set lower for smoother animation, higher for faster simulation
int runs_per_loop = 10000;

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
    w      = World();
    spore1 = color(128, 172, 255); //@diff(color_range)
    spore2 = color(64, 128, 255); //@diff(color_range)
    spore3 = color(255, 128, 172); //@diff(color_range)
    spore4 = color(255, 64, 128); //@diff(color_range)
    numcells = 0;
    cells.clear();
    seed();
}

void seed() {
    loadPixels();
    // Add cells at random places
    for (int i = 0; i < maxcells; i++) {
        int   cX = int(random(width));
        int   cY = int(random(height));
        int   c;
        float r = random(1);
        if (r < 0.25) {
            c = spore1;
        } else if (r < 0.5) {
            c = spore2;
        } else if (r < 0.75) {
            c = spore3;
        } else {
            c = spore4;
        }
        uint32_t pixel_color = w.getpix(cX, cY);
        if (pixel_color == black) {
            w.setpix(cX, cY, c);
            cells.emplace_back(cX, cY, w, spore1, spore2, spore3, spore4);
            numcells++;
        }
    }
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
    // background(0.f,0.f,0.f); //@diff(color_range) // note: this does not clear the pixels array. should call the clear() but is not implemented
    loadPixels();
    uint32_t black = color(0.f, 0.f, 0.f); //@diff(color_range)
    std::fill(pixels, pixels + (int)width * (int)height, black);
    updatePixels();
}


void mousePressed() {
    reset();
}

/*
note: inside the clearScreen(), the original examples used background() but this does not clear the pixel buffer in umfeld. 
*/