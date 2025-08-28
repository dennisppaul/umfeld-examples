/**
 * Pointillism
 * by Daniel Shiffman. 
 * 
 * Mouse horizontal location controls size of dots. 
 * Creates a simple pointillist effect using ellipses colored
 * according to pixels in an image. 
 */
#include "Umfeld.h"

using namespace umfeld;

PImage* img; //@diff(pointer)
int     smallPoint, largePoint;

void settings() {
    size(640, 360);
}

void setup() {
    img        = loadImage("moonwalk.jpg");
    smallPoint = 4;
    largePoint = 40;
    // imageMode(CENTER);
    noStroke();
    background(1.f); //@diff(color_range)
}

void draw() {
  float pointillize = map(mouseX, 0, width, smallPoint, largePoint);
  int x = int(random(img->width)); //@diff(pointer)
  int y = int(random(img->height)); //@diff(pointer)
  uint32_t pix = img->get(x, y); //@diff(pointer)

  fill( //@diff(color)
    red(pix),
    green(pix),
    blue(pix),
    0.5f
  );

  ellipse(x, y, pointillize, pointillize);
}
/*
note:
- i see a general conflict between the different color representations (eg. uint32_t vs. float)
- i suggest either one of the following:
    - use uint32_t for the `default` color representation, and everything that uses float should be a wrapper with a function suffixed `_f` that runs the uint32_t function internally.
    - use float for the `default` color representation, and everything that uses uint32_t should be a wrapper with a function suffixed with `_i` that runs the float function internally.
*/