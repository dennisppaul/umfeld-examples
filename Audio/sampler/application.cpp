/*
 * this example demonstrates how to load a sample and apply a low pass filter
 * to it. it also shows how to resample a sample to a different sample rate.
 */

#include "Umfeld.h"
#include "audio/Sampler.h"
#include "audio/LowPassFilter.h"

using namespace umfeld;

Sampler*       sampler;
LowPassFilter* filter;

void settings() {
    size(1024, 768);
    audio();
}

void setup() {
    sampler = loadSample("teilchen.wav");
    // resample sample to double the sample rate i.e the amount of samples per second
    // const float sampler_sample_rate = sampler->get_sample_rate();
    // sampler->resample(sampler_sample_rate, sampler_sample_rate * 2);
    sampler->set_looping();
    sampler->play();

    filter = new LowPassFilter(get_audio_sample_rate());

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

    filter->set_frequency(map(mouseX, 0, width, 20.0f, 8000.0f));
    filter->set_resonance(map(mouseY, 0, height, 0.1f, 0.9f));
}

void keyPressed() {
    if (key == '1') {
        sampler->rewind();
        sampler->play();
    }
}

void keyReleased() {
    if (key == '2') {
        sampler->stop();
    }
}

void audioEvent(const PAudio& audio) {
    float sample_buffer[audio.buffer_size];
    for (int i = 0; i < audio.buffer_size; i++) {
        float sample     = sampler->process();
        sample           = filter->process(sample);
        sample_buffer[i] = sample;
    }
    if (audio.output_channels == 2) {
        merge_interleaved_stereo(sample_buffer, sample_buffer, audio.output_buffer, audio.buffer_size);
    }
}

void shutdown() {
    delete sampler;
    delete filter;
}