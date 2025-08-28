/**
 * Scrollbar.
 *
 * Move the scrollbars left and right to change the positions of the images.
 */
#include "Umfeld.h"
#include "Scrollbar.h"

using namespace umfeld;

//True if a mouse button was pressed while no other button was.
bool       firstMousePress = false; //@diff(generic_type)
HScrollbar hs1, hs2;                // Two scrollbars
PImage     *img1, *img2;              // Two images to load //@diff(pointer)


void settings() {
    size(640, 360);
}

void setup() {
    noStroke();

    hs1 = HScrollbar(0, height / 2 - 8, width, 16, 16, &firstMousePress);
    hs2 = HScrollbar(0, height / 2 + 8, width, 16, 16, &firstMousePress);

    // Load images
    img1 = loadImage("seedTop.jpg");
    img2 = loadImage("seedBottom.jpg");
}

void draw() {
    background(1.f); //@diff(color_range)

    // Get the position of the img1 scrollbar
    // and convert to a value to display the img1 image
    float img1Pos = hs1.getPos() - width / 2;
    fill(1.f); //@diff(color_range)
    image(img1, width / 2 - img1->width / 2 + img1Pos * 1.5, 0);

    // Get the position of the img2 scrollbar
    // and convert to a value to display the img2 image
    float img2Pos = hs2.getPos() - width / 2;
    fill(1.f); //@diff(color_range)
    image(img2, width / 2 - img2->width / 2 + img2Pos * 1.5, height / 2);

    hs1.update();
    hs2.update();
    hs1.display();
    hs2.display();

    stroke(0.f); //@diff(color_range)
    line(0, height / 2, width, height / 2);

    //After it has been used in the sketch, set it back to false
    if (firstMousePress) {
        firstMousePress = false;
    }
}

void mousePressed() {
    if (!firstMousePress) {
        firstMousePress = true;
    }
}
