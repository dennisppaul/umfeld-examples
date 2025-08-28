#pragma once
#include "Umfeld.h"

using namespace umfeld;

// Class for animating a sequence of GIFs

class Animation {
public:
    std::vector<PImage*> images; //@diff(std::vector)
    int imageCount;
    int frame;

    Animation() : imageCount(0), frame(0) {} //@diff(default constructor)

    Animation(std::string imagePrefix, int count) {
        imageCount = count;
        images.resize(imageCount); //@diff(std::vector)

        for (int i = 0; i < imageCount; i++) {
            // Use nf() to number format 'i' into four digits
            std::string filename = imagePrefix + nf(i, 4) + ".gif";
            images[i] = loadImage(filename);
        }
    }

    void display(float xpos, float ypos) {
        frame = (frame + 1) % imageCount;
        image(images[frame], xpos, ypos);
    }

    int getWidth() {
        return images[0]->width;
    }
};
