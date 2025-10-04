#include "Umfeld.h"
#include "audio/ADSR.h"
#include "audio/Trigger.h"
#include "audio/Wavetable.h"

using namespace umfeld;

Wavetable* wavetable_oscillator;
Wavetable* lfo;
ADSR*      adsr;
Trigger*   trigger;
bool       toggle = false;

void settings() {
    size(1024, 768);
    audio(0, 2);
}

void beat(const int event) {
    if (event == EVENT_RISING_EDGE) {
        adsr->start();
        toggle = true;
    } else {
        adsr->stop();
        toggle = false;
    }
}

void setup() {
    adsr    = new ADSR(get_audio_sample_rate());
    trigger = new Trigger();
    trigger->set_callback(beat);

    lfo = new Wavetable(2048, get_audio_sample_rate());
    lfo->set_waveform(WAVEFORM_TRIANGLE);
    lfo->set_frequency(1.0f);

    wavetable_oscillator = new Wavetable(1024,get_audio_sample_rate());
    wavetable_oscillator->set_waveform(WAVEFORM_SAWTOOTH_HARMONICS, 8);
    wavetable_oscillator->set_frequency(110.0f);
    wavetable_oscillator->set_amplitude(0.5f);

    if (get_audio_output_channels() != 2) {
        error("this example requires a stereo output");
        exit(1);
    }
}

void draw() {
    background(0.85f);

    if (toggle) {
        noStroke();
        fill(1.0f, 0.25f, 0.35f);
        circle(width / 2.0f, height / 2.0f, 100);
    } else {
        noFill();
        stroke(1.0f, 0.25f, 0.35f);
        circle(width / 2.0f, height / 2.0f, 100);
    }

    lfo->set_frequency(map(mouseY, 0, height, 0.1f, 10.0f));
}

void audioEvent(const PAudio& audio) {
    float sample_buffer[audio.buffer_size];
    for (int i = 0; i < audio.buffer_size; i++) {
        /* feed lfo to trigger */
        trigger->process(lfo->process());
        /* process sample */
        float sample     = wavetable_oscillator->process();
        sample           = adsr->process(sample);
        sample_buffer[i] = sample;
    }
    if (audio.output_channels == 2) {
        merge_interleaved_stereo(sample_buffer, sample_buffer, audio.output_buffer, audio.buffer_size);
    }
}

void shutdown() {
    delete wavetable_oscillator;
    delete lfo;
    delete adsr;
    delete trigger;
}