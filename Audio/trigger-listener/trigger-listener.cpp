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

class MyTriggerListener final : public TriggerListener {
public:
    void trigger(const int event) override {
        if (event == EVENT_RISING_EDGE) {
            adsr->start();
            toggle = true;
        } else if (event == EVENT_FALLING_EDGE) {
            adsr->stop();
            toggle = false;
        }
    }
};

MyTriggerListener trigger_listener;

void settings() {
    size(1024, 768);
    audio(0, 2);
}

void setup() {
    adsr    = new ADSR(audio_sample_rate);
    trigger = new Trigger();
    trigger->add_listener(&trigger_listener);

    lfo = new Wavetable(2048, audio_sample_rate);
    lfo->set_waveform(WAVEFORM_SINE);
    lfo->set_frequency(1.0f);

    wavetable_oscillator = new Wavetable(1024, audio_sample_rate);
    wavetable_oscillator->set_waveform(WAVEFORM_SQUARE_HARMONICS, 8);
    wavetable_oscillator->set_frequency(110.0f);
    wavetable_oscillator->set_amplitude(0.5f);
}

void draw() {
    background(0.85f);

    if (toggle) {
        noStroke();
        fill(0.5f, 0.85f, 1.0f);
        circle(width / 2.0f, height / 2.0f, 100);
    } else {
        noFill();
        stroke(0.5f, 0.85f, 1.0f);
        circle(width / 2.0f, height / 2.0f, 100);
    }

    lfo->set_frequency(map(mouseY, 0, height, 0.1f, 10.0f));
}

void audioEvent() {
    float sample_buffer[audio_buffer_size];
    for (int i = 0; i < audio_buffer_size; i++) {
        /* feed lfo to trigger */
        trigger->process(lfo->process());
        /* process sample */
        float sample     = wavetable_oscillator->process();
        sample           = adsr->process(sample);
        sample_buffer[i] = sample;
    }
    merge_interleaved_stereo(sample_buffer, sample_buffer, audio_output_buffer, audio_buffer_size);
}

void shutdown() {
    delete wavetable_oscillator;
    delete lfo;
    delete adsr;
    delete trigger;
}