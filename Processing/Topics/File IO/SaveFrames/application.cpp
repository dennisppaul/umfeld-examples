/**
 * Save Frames
 * by Daniel Shiffman.  
 * 
 * This example demonstrates how to use saveFrame() to render
 * out an image sequence that you can assemble into a movie
 * using the MovieMaker tool.
 */
#include "Umfeld.h"

using namespace umfeld;

// A boolean to track whether we are recording are not
bool recording = false; //@diff(generic_type)

void settings() {
    size(640, 360);
}

void setup() {
    textFont(loadFont("SourceCodePro-Regular.ttf", 12));
}

void draw() {
    background(0.f); //@diff(color_range)

    // An arbitrary oscillating rotating animation
    // so that we have something to render
    for (float a = 0; a < TWO_PI; a += 0.2) {
        pushMatrix();
        translate(width / 2, height / 2);
        rotate(a + sin(frameCount * 0.004 * a));
        stroke(1.f); //@diff(color_range)
        line(-100, 0, 100, 0);
        popMatrix();
    }

    // If we are recording call saveFrame!
    // The number signs (#) indicate to Processing to
    // number the files automatically
    if (recording) {
        // saveFrame("output/" + to_string(frameCount) + ".png"); // this fails silently if the directory does not exist
        saveFrame();
    }

    // Let's draw some stuff to tell us what is happening
    // It's important to note that none of this will show up in the
    // rendered files b/c it is drawn *after* saveFrame()
    textAlign(CENTER);
    fill(1.f); //@diff(color_range)
    if (!recording) {
        text("Press r to start recording.", width / 2, height - 24);
    } else {
        text("Press r to stop recording.", width / 2, height - 24);
    }

    // A red dot for when we are recording
    stroke(1.f); //@diff(color_range)
    if (recording) {
        fill(1.f, 0.f, 0.f); //@diff(color_range)
    } else {
        noFill();
    }
    ellipse(width / 2, height - 48, 16, 16);
}

void keyPressed() {

    // If we press r, start or stop recording!
    if (key == 'r' || key == 'R') {
        recording = !recording;
    }
}
