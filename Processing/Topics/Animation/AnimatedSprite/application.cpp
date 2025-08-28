/**
 * Animated Sprite (Shifty + Teddy)
 * by James Paterson. 
 * 
 * Press the mouse button to change animations.
 * Demonstrates loading, displaying, and animating GIF images.
 * It would be easy to write a program to display 
 * animated GIFs, but would not allow as much control over 
 * the display sequence and rate of display. 
 */

#include "Umfeld.h"
#include "Animation.h"

using namespace umfeld;

Animation animation1, animation2;

float xpos;
float ypos;
float drag = 30.0;

void settings() {
    size(640, 360);
}

void setup() {
    background(1.f, .8f, 0.f); //@diff(color_range)
    set_frame_rate(24); //@diff(frameRate)
    animation1 = Animation("PT_Shifty_", 38);
    animation2 = Animation("PT_Teddy_", 60);
    ypos       = height * 0.25;
}

void draw() {
    float dx = mouseX - xpos;
    xpos     = xpos + dx / drag;

    // Display the sprite at the position xpos, ypos
    if (isMousePressed) { //@diff(mousePressed)
        background(.6f, .6f, 0.f); //@diff(color_range)
        animation1.display(xpos - animation1.getWidth() / 2, ypos);
    } else {
        background(1.f, .8f, 0.f); //@diff(color_range)
        animation2.display(xpos - animation1.getWidth() / 2, ypos);
    }
}
