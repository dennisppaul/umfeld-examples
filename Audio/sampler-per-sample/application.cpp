/*
 * this example demonstrates how to load a sample and play it back sample by sample.
 */

#include "Umfeld.h"
#include "audio/Sampler.h"
#include "audio/LowPassFilter.h"

using namespace umfeld;

Sampler* sampler;

void settings() {
    size(1024, 768);
    audio();
    enable_audio_per_sample_processing = true;
}

void setup() {
    sampler = loadSample("teilchen.wav");
    sampler->set_looping();
    sampler->play();

    if (get_audio_output_channels() != 2) {
        error("this example requires a stereo output");
        exit(1);
    }
}

void draw() {
    background(0.85f);

    const float size = height / 2.0f;
    const float x    = width / 2.0f;
    const float y    = height / 2.0f;

    strokeWeight(16.0f);
    noFill();
    stroke(1.0f, 0.25f, 0.35f);
    arc(x, y, size, size, -HALF_PI, TWO_PI * sampler->get_position_normalized() - HALF_PI);
}

void audioEvent(float& left, float& right) {
    const float sample = sampler->process();
    left               = sample;
    right              = sample;
}

void shutdown() {
    delete sampler;
}