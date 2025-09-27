/*
 * this example demonstrates how to generate a wavetable oscillator sound with ADSR envelope and reverb.
 */

#include "Umfeld.h"
#include "audio/AudioUtilities.h"

using namespace umfeld;

float energy = 0.0f;

void settings() {
    size(1024, 768);
    audio(1, 2);
}

void setup() {}

void draw() {
    background(0.85f);
    noFill();
    stroke(1.0f, 0.25f, 0.35f);
    circle(width * 0.5f, height * 0.5f, energy * 0.5f * height + 0.5f * height);
}

// NOTE prefer this over `audioEvent()`
void audioEvent(const PAudio& audio) {
    for (uint32_t i = 0; i < audio.buffer_size; ++i) {
        audio.output_buffer[i] = audio.input_buffer[i];
    }
    // mix_mono_to_stereo(src_sample_buffer, audio); // NOTE mix mono sample buffer to audio’s stereo output ( assumes audio.output_channels == 2 and evaluates audio.is_interleaved )
    // mix_mono_to_stereo(src_sample_buffer,         // NOTE mix mono input to stereo output ( evaluates interleaved state )
    //                    dst_sample_buffer,
    //                    src_dst_buffer_size, // NOTE buffer_size i.e number of frames must match
    //                    is_interleaved);
    // mix_stereo_to_mono(src_sample_buffer_left, // NOTE mix stereo input to mono output ( evaluates interleaved state )
    //                    src_sample_buffer_right,
    //                    dst_sample_buffer,
    //                    src_dst_buffer_size, // NOTE buffer_size i.e number of frames must match
    //                    is_interleaved);
    // merge_interleaved_stereo(sample_buffer_left,
    //                          sample_buffer_right,
    //                          dst_buffer_stereo,
    //                          buffer_size);
}

void audioEvent() {
    for (uint32_t i = 0; i < audio_device->buffer_size; ++i) {
        audio_device->output_buffer[i] = audio_device->input_buffer[i];
    }
    for (uint32_t i = 0; i < audio_buffer_size; ++i) {
        audio_output_buffer[i] = audio_input_buffer[i];
    }
    // merge_interleaved_stereo(sample_buffer, sample_buffer, audio_output_buffer, audio_buffer_size);
}

void shutdown() {}