#include "Umfeld.h"

using namespace umfeld;


uint32_t hsb_to_rgb_packed(const float h, const float s, const float b, const float a = 1.0f) {
    float r = 0, g = 0, bl = 0;
    float hh = h * 6.0f; // h in [0,1] mapped to [0,6]
    int i = static_cast<int>(hh);
    float f = hh - i;
    float p = b * (1.0f - s);
    float q = b * (1.0f - s * f);
    float t = b * (1.0f - s * (1.0f - f));
    switch (i % 6) {
        case 0: r = b; g = t; bl = p; break;
        case 1: r = q; g = b; bl = p; break;
        case 2: r = p; g = b; bl = t; break;
        case 3: r = p; g = q; bl = b; break;
        case 4: r = t; g = p; bl = b; break;
        case 5: r = b; g = p; bl = q; break;
    }
    return static_cast<uint32_t>(a * 255) << 24 |
           static_cast<uint32_t>(bl * 255) << 16 |
           static_cast<uint32_t>(g * 255) << 8 |
           static_cast<uint32_t>(r * 255);
}

int barWidth = 20;
int lastBar = -1;


void settings(){
    size(640, 360);
}

void setup() {
  noStroke();
  background(0.f);
}

void draw() {
  int whichBar = mouseX / float(barWidth);
  if (whichBar != lastBar) {
    int barX = whichBar * barWidth;
    glm::vec3 hsb;
    hsb.x = mouseY/height;
    hsb.y = 1.f;
    hsb.z = 1.f;
    uint32_t packed = hsb_to_rgb_packed(hsb.x, hsb.y, hsb.z);

    fill_color(packed);
    rect(barX, 0, barWidth, height);
    lastBar = whichBar;
  }
}
