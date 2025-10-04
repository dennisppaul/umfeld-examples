/*
 * this example demonstrates how to configure an audio device.
 */

#include "Umfeld.h"
#include "audio/Sampler.h"
#include "audio/LowPassFilter.h"

using namespace umfeld;

Sampler*       sampler;
LowPassFilter* filter;

void settings() {
    size(1024, 768);
    /* use AudioUnitInfo to specifiy audio settings */
    AudioUnitInfo info;
    info.input_channels  = 0;
    info.output_channels = 2;
    info.threaded        = true;
    audio(info);
    /* select audio driver with `subsystem_audio = ...`. SDL is currently the default */
    // subsystem_audio = umfeld_create_subsystem_audio_sdl();
    subsystem_audio = umfeld_create_subsystem_audio_portaudio();
}

void setup() {
    sampler = loadSample("teilchen.wav");
    sampler->set_looping();
    sampler->play();

    filter = new LowPassFilter(get_audio_sample_rate());

    // 'get_audio_output_channels()' returns the number of output channels of the default audio device.
    // note that 'audio()' requests a certain number of channels but the actual device might provide a different number.
    if (get_audio_output_channels() != 2) {
        error("this example requires a stereo output");
        exit(1);
    }
}

void draw() {
    background(0.85f);
    noFill();
    stroke(1.0f, 0.25f, 0.35f);
    const float size = 50.0f;
    const float x    = width / 2.0f;
    const float y    = height / 2.0f;
    line(x - size, y - size, x + size, y + size);
    line(x - size, y + size, x + size, y - size);

    filter->set_frequency(map(mouseX, 0, width, 20.0f, 8000.0f));
    filter->set_resonance(map(mouseY, 0, height, 0.1f, 0.9f));
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