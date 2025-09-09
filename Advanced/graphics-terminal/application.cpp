#include "Umfeld.h"
#include "PGraphicsTerminal.h"

using namespace umfeld;

PImage* umfeld_image;

void settings() {
    // size(1024, 768); // TODO values have no effect ( defined by actual terminal window size ), but this needs to be called or else there is no graphics subsystem created
    // NOTE using `size(...)` with terminal renderer has no effect. the size is determined by the actual terminal window size.
    //      since `size(...)` is not called, graphic output must be enabled manually e.g by calling `enable_graphics_subsystem()`.
    //      this also defines the terminal renderer.
    PGraphicsTerminal::enable_graphics_subsystem();
}

void setup() {
    umfeld_image = loadImage("umfeld-logotype-16.png");
    // NOTE renderer specific options can be set like this:
    //      PGraphicsTerminal* gt = (PGraphicsTerminal*)g;
    //      gt->auto_refresh(true);
    //      gt->simple_clear = false;
    // NOTE adjust debounce interval to prevent key released events from firing prematurely:
    //      umfeld::subsystem::graphics_terminal::set_debounce_interval(5);
}

bool keyPressedCallback = false;
int  keyReleasedCounter = 0;

void draw() {
    background(0.2f);

    stroke(0.5f, 0.85f, 1.0f);
    line(0, 0, mouseX, mouseY);

    stroke(1.0f, 0.25f, 0.35f);
    point(mouseX, mouseY - 1);

    fill(1.0f, 1.0f, 1.0f);
    text(to_string("size: ", width, "x", height), 0, 0);
    text(to_string("mouse: ", mouseX, "x", mouseY), mouseX, mouseY);
    text(to_string("image: ", umfeld_image->width, "x", umfeld_image->height), mouseX, mouseY + 1);

    fill(1.0f, 0.25f, 0.35f);
    image(umfeld_image, mouseX, mouseY + 2, 32, 16);

    stroke(1.0f, 1.0f, 1.0f);
    rect(mouseX, mouseY + 2, 32, 16);

    fill(1.0f);
    text(to_string(
             "key: ", key,
             " :: ", (isKeyPressed ? "P" : "R"),
             " :: ", (keyPressedCallback ? "P" : "R"),
             " :: ", keyReleasedCounter),
         0, 1);
}

void keyPressed() {
    keyPressedCallback = true;
}

void keyReleased() {
    keyPressedCallback = false;
    keyReleasedCounter++;
}