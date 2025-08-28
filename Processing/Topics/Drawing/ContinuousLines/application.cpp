/**
 * Continuous Lines. 
 * 
 * Click and drag the mouse to draw a line. 
 */
#include "Umfeld.h"

using namespace umfeld;

static int lastMouseX = 0; //DEBUG
static int lastMouseY = 0; //DEBUG

void settings() {
    size(640, 360);
}

void setup() {
    background(.4f); //@diff(color_range)
    lastMouseX = mouseX; //DEBUG
    lastMouseY = mouseY; //DEBUG
}


void draw() {
    printf("Current mouseY value: %d\n", mouseY);
    stroke(1.f);
    if (isMousePressed == true) {
        printf("Before update - lastMouseY: %d, mouseY: %d\n", lastMouseY, mouseY);
        printf("Drawing line: (%d,%d) to (%d,%d)\n", mouseX, mouseY, lastMouseX, lastMouseY);
        line(mouseX, mouseY, lastMouseX, lastMouseY);
    }
    lastMouseX = mouseX;
    printf("Setting lastMouseY from %d to %d\n", lastMouseY, mouseY);
    lastMouseY = mouseY;
    printf("After update - lastMouseY: %d\n", lastMouseY);
}

/*
* note: mouse coordinate inconsistency issue
* 
* problem: mouseY shows inconsistent values within single frame execution.
*          mouseY shows -2147483648 (which is INT_MIN) suggesting uninitialized memory
* 
* possible reason: umfeld's event processing system creates race condition:
* 1. SDL mouse events are cached in event_cache during SDL_AppEvent()
* 2. events processed during SDL_AppIterate() via event_in_update_loop()
* 3. multiple mouse motion events can update mouseX/mouseY MID-FRAME
* 4. user draw() function sees different values between consecutive accesses
* 
* some details:
* - SubsystemHIDEvents::handle_event() updates global mouseX/mouseY variables
* - event cache can contain multiple SDL_EVENT_MOUSE_MOTION events per frame
* - processing happens DURING user draw() execution, not before/after
* 
* possible solution: capture mouse coordinates once at start of draw() to avoid
* reading variables that change mid-execution due to event processing.
* 
* 
* location: 
*            case SDL_EVENT_MOUSE_MOTION
*               :umfeld/src/SubsystemHIDEvents.cpp:86-96 (mouse updates)
*           
*            SDL_AppResult SDL_AppIterate(void* appstate) 
*               :umfeld/src/Umfeld.cpp:578-587
*/

