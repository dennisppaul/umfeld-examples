/**
 * Thread function example
 * by Daniel Shiffman.  
 * 
 * This example demonstrates how to use thread() to spawn
 * a process that happens outside of the main animation thread.
 *
 * When thread() is called, the draw() loop will continue while
 * the code inside the function passed to thread() will operate
 * in the background.
 *
 */
#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(640, 360);
}

void setup() {
    noFill();
    stroke(1.0f, 0.25f, 0.35f);
}

void draw() {
    background(0.85f);
    const float size = 50.0f;
    const float x    = width / 2.0f;
    const float y    = height / 2.0f;
    line(x - size, y - size, x + size, y + size);
    line(x - size, y + size, x + size, y - size);
}
/*
note:
- thread is unimplemented
*/