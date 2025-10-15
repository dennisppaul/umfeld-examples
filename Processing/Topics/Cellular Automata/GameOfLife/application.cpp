/**
 * Game of Life
 *
 * Press SPACE BAR to pause and change the cell's values 
 * with the mouse. On pause, click to activate/deactivate 
 * cells. Press 'R' to randomly reset the cells' grid. 
 * Press 'C' to clear the cells' grid. The original Game 
 * of Life was created by John Conway in 1970.
 * 
 * For umfeld, the drawing part is optimized to speed up the
 * performance of the sketch. The dead and alive cells  are 
 * drawn in a single OpenGL call, which is much faster.
 * 
 */
#include "Umfeld.h"
#include <chrono>

using namespace umfeld;

// Size of cells
int cellSize = 5;

// How likely for a cell to be alive at start (in percentage)
float probabilityOfAliveAtStart = 15;

// Variables for timer
int interval         = 100;
int lastRecordedTime = 0;

// Colors for active/inactive cells
uint32_t alive = color(0.f, .78f, 0.f); //@diff(color_type)
uint32_t dead  = color(0.f);            //@diff(color_type)

// Array of cells
std::vector<std::vector<int>> cells; //@diff(std::vector)
// Buffer to record the state of the cells and use this
// while changing the others in the interations
std::vector<std::vector<int>> cellsBuffer; //@diff(std::vector)

// Pause
bool pause = false; //@diff(generic_type)

void iteration(); //@diff(forward_declaration)

void settings() {
    size(640, 360);
}

void setup() {
    // Instantiate arrays
    int cols = width / cellSize;
    int rows = height / cellSize;
    cells.resize(cols);
    cellsBuffer.resize(cols);
    for (int i = 0; i < cols; i++) {
        cells[i].resize(rows, 0);
        cellsBuffer[i].resize(rows, 0);
    }

    // This stroke will draw the background grid
    stroke(.18f); //@diff(color_range)

    hint(DISABLE_SMOOTH_LINES); //@diff(available_hint)
    hint(DISABLE_DEPTH_TEST);   //@diff(available_hint)

    // Initialization of cells
    for (int x = 0; x < width / cellSize; x++) {
        for (int y = 0; y < height / cellSize; y++) {
            float state = random(100);
            if (state > probabilityOfAliveAtStart) {
                state = 0;
            } else {
                state = 1;
            }
            cells[x][y] = int(state); // Save state of each cell
        }
    }
    // Fill in black in case cells don't cover all the windows
    background(0.f); //@diff(color_range)
}


void draw() {

    //Draw grid
    // The umfeld version of optimization happens here.
    // We separate the draw of alive and dead cells as well as the grid lines
    // so that we can draw all the rectangles/lines with the same color
    // in a single OpenGL call, which is much faster

    noStroke();

    // Draw alive cells
    fill_color_32(alive);
    beginShape(TRIANGLES);
    for (int x = 0; x < width / cellSize; x++) {
        for (int y = 0; y < height / cellSize; y++) {
            if (cells[x][y] == 1) {
                // Draw rectangle as two triangles (6 vertices total)
                // First triangle: top-left, top-right, bottom-left
                vertex(x * cellSize, y * cellSize);            // top-left
                vertex(x * cellSize + cellSize, y * cellSize); // top-right
                vertex(x * cellSize, y * cellSize + cellSize); // bottom-left

                // Second triangle: top-right, bottom-right, bottom-left
                vertex(x * cellSize + cellSize, y * cellSize); // top-right
                vertex(x * cellSize + cellSize, y * cellSize + cellSize); // bottom-right
                vertex(x * cellSize, y * cellSize + cellSize); // bottom-left
            }
        }
    }
    endShape();

    // Draw dead cells
    fill_color_32(dead);
    beginShape(TRIANGLES);
    for (int x = 0; x < width / cellSize; x++) {
        for (int y = 0; y < height / cellSize; y++) {
            if (cells[x][y] == 0) {
                // Draw rectangle as two triangles (6 vertices total)
                // First triangle: top-left, top-right, bottom-left
                vertex(x * cellSize, y * cellSize);            // top-left
                vertex(x * cellSize + cellSize, y * cellSize); // top-right
                vertex(x * cellSize, y * cellSize + cellSize); // bottom-left

                // Second triangle: top-right, bottom-right, bottom-left
                vertex(x * cellSize + cellSize, y * cellSize); // top-right
                vertex(x * cellSize + cellSize, y * cellSize + cellSize); // bottom-right
                vertex(x * cellSize, y * cellSize + cellSize); // bottom-left
            }
        }
    }
    endShape();

    // Draw grid lines
    stroke(.18f);
    beginShape(LINES);
    // Vertical lines
    for (int x = 0; x <= width / cellSize; x++) {
        vertex(x * cellSize, 0);
        vertex(x * cellSize, height);
    }
    // Horizontal lines
    for (int y = 0; y <= height / cellSize; y++) {
        vertex(0, y * cellSize);
        vertex(width, y * cellSize);
    }
    endShape();

    // Iterate if timer ticks
    if (millis() - lastRecordedTime > interval) {
        if (!pause) {
            iteration();
            lastRecordedTime = millis();
        }
    }

    // Create  new cells manually on pause
    if (pause && isMousePressed) {
        // Map and avoid out of bound errors
        int xCellOver = int(map(mouseX, 0, width, 0, width / cellSize));
        xCellOver     = constrain(xCellOver, 0, int(width / cellSize - 1));
        int yCellOver = int(map(mouseY, 0, height, 0, height / cellSize));
        yCellOver     = constrain(yCellOver, 0, int(height / cellSize - 1));

        // Check against cells in buffer
        if (cellsBuffer[xCellOver][yCellOver] == 1) { // Cell is alive
            cells[xCellOver][yCellOver] = 0;          // Kill
            fill_color_32(dead);                         // Fill with kill color
        } else {                                      // Cell is dead
            cells[xCellOver][yCellOver] = 1;          // Make alive
            fill_color_32(alive);                        // Fill alive color
        }
    } else if (pause && !isMousePressed) { // And then save to buffer once mouse goes up
        // Save cells to buffer (so we opeate with one array keeping the other intact)
        for (int x = 0; x < width / cellSize; x++) {
            for (int y = 0; y < height / cellSize; y++) {
                cellsBuffer[x][y] = cells[x][y];
            }
        }
    }
}


void iteration() { // When the clock ticks
    // Save cells to buffer (so we opeate with one array keeping the other intact)
    for (int x = 0; x < width / cellSize; x++) {
        for (int y = 0; y < height / cellSize; y++) {
            cellsBuffer[x][y] = cells[x][y];
        }
    }

    // Visit each cell:
    for (int x = 0; x < width / cellSize; x++) {
        for (int y = 0; y < height / cellSize; y++) {
            // And visit all the neighbours of each cell
            int neighbours = 0; // We'll count the neighbours
            for (int xx = x - 1; xx <= x + 1; xx++) {
                for (int yy = y - 1; yy <= y + 1; yy++) {
                    if (((xx >= 0) && (xx < width / cellSize)) && ((yy >= 0) && (yy < height / cellSize))) { // Make sure you are not out of bounds
                        if (!((xx == x) && (yy == y))) {                                                     // Make sure to to check against self
                            if (cellsBuffer[xx][yy] == 1) {
                                neighbours++; // Check alive neighbours and count them
                            }
                        } // End of if
                    } // End of if
                } // End of yy loop
            } //End of xx loop
            // We've checked the neigbours: apply rules!
            if (cellsBuffer[x][y] == 1) { // The cell is alive: kill it if necessary
                if (neighbours < 2 || neighbours > 3) {
                    cells[x][y] = 0; // Die unless it has 2 or 3 neighbours
                }
            } else { // The cell is dead: make it live if necessary
                if (neighbours == 3) {
                    cells[x][y] = 1; // Only if it has 3 neighbours
                }
            } // End of if
        } // End of y loop
    } // End of x loop
} // End of function

void keyPressed() {
    if (key == 'r' || key == 'R') {
        // Restart: reinitialization of cells
        for (int x = 0; x < width / cellSize; x++) {
            for (int y = 0; y < height / cellSize; y++) {
                float state = random(100);
                if (state > probabilityOfAliveAtStart) {
                    state = 0;
                } else {
                    state = 1;
                }
                cells[x][y] = int(state); // Save state of each cell
            }
        }
    }
    if (key == ' ') { // On/off of pause
        pause = !pause;
    }
    if (key == 'c' || key == 'C') { // Clear all
        for (int x = 0; x < width / cellSize; x++) {
            for (int y = 0; y < height / cellSize; y++) {
                cells[x][y] = 0; // Save all to zero
            }
        }
    }
}
