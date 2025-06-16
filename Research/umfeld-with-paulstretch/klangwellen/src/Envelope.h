/*
 * KlangWellen
 *
 * This file is part of the *KlangWellen* library (https://github.com/dennisppaul/klangwellen).
 * Copyright (c) 2024 Dennis P Paul
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * PROCESSOR INTERFACE
 *
 * - [x] float process()
 * - [ ] float process(float)
 * - [ ] void process(AudioSignal&)
 * - [x] void process(float*, uint32_t) *overwrite*
 * - [ ] void process(float*, float*, uint32_t)
 */

/**
 * envelope with multiple stages. the envelope is configured with value and duration defined in <code>Stage</code>. once
 * started the envelope interpolates linearly from current stage value to next stage value in current stage’s duration.
 * by definition the duration of the last stage is ignored.
 * <p>
 * a typical application of an envelope could look as follows:
 * <pre>
 * <code>
 *     Envelope mEnvelope = new Envelope();
 *     mEnvelope.add_stage(0.0f, 2.0f);
 *     mEnvelope.add_stage(1.0f, 5.0f);
 *     mEnvelope.add_stage(0.0f);
 * </code>
 * </pre>
 * the code above would read as follows:
 * <ul>
 * <li>interpolate from <code>0.0</code> ( value of 1st stage ) to <code>1.0</code> ( value of 2nd stage ) in
 * <code>2.0</code> seconds ( duration of 1st stage )
 * <li>interpolate from <code>1.0</code> to <code>0.0</code> in <code>5.0</code> seconds
 * <li>envelope is done
 * </ul>
 * <p>
 * the following example creates a simple ramp:
 * <pre>
 * <code>
 *     Envelope mEnvelope = new Envelope();
 *     mEnvelope.add_stage(0.0f, 2.0f);
 *     mEnvelope.add_stage(1.0f);
 * </code>
 * </pre>
 * the code above would read as follows:
 * <ul>
 * <li>interpolate from <code>0.0</code> to <code>1.0</code> in <code>2.0</code> seconds
 * <li>envelope is done
 * </ul>
 */

#pragma once

#include <stdint.h>
#include <stdio.h>

#include <vector>

#include "KlangWellen.h"
#include "AudioSignal.h"

namespace klangwellen {
    class Envelope {
        /*
         *
         *          Stages(S)
         *
         *          |S0-----|S1--|S2-|S3--|S4---
         *          |      /\
         *          |     /  \      /\
         *          |    /    \    /  \
         *          |   /      \  /    \
         *          |  /        \/      \
         *          | /                  \______
         *          |/__________________________
         *          |0>>>>>>1>>>>0.3>0.7>>0.1>>>
         *       )
         *
         */
    public:
        class Stage {
        public:
            /**
             * stage duration in seconds
             */
            float duration;
            /**
             * stage starting value
             */
            float value;

            Stage(float pValue = 0.0, float pDuration = 0.0) {
                duration = pDuration;
                value    = pValue;
            }
        };

        Envelope(uint32_t sample_rate = KlangWellen::DEFAULT_SAMPLE_RATE) : fSampleRate(sample_rate) {
        }

        /**
         * enable looping of envelope. once the last stage has completed the envelope is reset to the first stage and
         * repeats.
         *
         * @param pLoop flag to enable looping.
         */
        void enable_loop(bool pLoop) {
            fLoop = pLoop;
        }

        /**
         * advance envelope on step
         *
         * @return current value
         */
        float process() {
            if (!fEnvelopeDone) {
                const int mNumberOfStages = fEnvelopeStages.size();
                if (fEnvStage < mNumberOfStages) {
                    fValue += fTimeScale * fDelta;
                    fStageDuration += fTimeScale * 1.0f / fSampleRate;
                    if (fStageDuration > fEnvelopeStages[fEnvStage].duration) {
                        const float mRemainder = fStageDuration - fEnvelopeStages[fEnvStage].duration;
                        finished_stage(fEnvStage);
                        fEnvStage++;
                        if (fEnvStage < mNumberOfStages - 1) {
                            prepareNextStage(fEnvStage, mRemainder);
                        } else {
                            stop();
                            finished_envelope();
                        }
                    }
                }
            }
            return fValue;
        }

        void process(float*         signal_buffer,
                     const uint32_t length = KlangWellen::DEFAULT_AUDIOBLOCK_SIZE) {
            for (uint32_t i = 0; i < length; i++) {
                signal_buffer[i] = process();
            }
        }

        /**
         * clears all current stages from the envelope and creates a ramp from start to end value in specified duration.
         *
         * @param pStartValue start value of ramp
         * @param pEndValue   end value of ramp
         * @param pDuration   duration of ramp
         */
        void ramp(float pStartValue, float pEndValue, float pDuration) {
            fEnvelopeStages.clear();
            add_stage(pStartValue, pDuration);
            add_stage(pEndValue);
        }

        /**
         * clears all current stages from envelope and creates a ramp from the current value to specified value in specified
         * duration. note, that the envelope might need to be restarted with `start()`.
         *
         * @param pValue    end value of ramp
         * @param pDuration duration of ramp
         */
        void ramp_to(float pValue, float pDuration) {
            fEnvelopeStages.clear();
            add_stage(fValue, pDuration);
            add_stage(pValue);
        }

        /**
         * @return list of all stages
         */
        std::vector<Stage>& stages() {
            return fEnvelopeStages;
        }

        /**
         * @param pValue    value of stage
         * @param pDuration duration of stage
         */
        void add_stage(float pValue, float pDuration) {
            fEnvelopeStages.push_back(Stage(pValue, pDuration));
        }

        /**
         * @param pValue value of stage
         */
        void add_stage(float pValue) {
            fEnvelopeStages.push_back(Stage(pValue, 0.0f));
        }

        /**
         *
         */
        void clear_stages() {
            fEnvelopeStages.clear();
        }

        /**
         *
         */
        void start() {
            fEnvelopeDone = false;
            if (!fEnvelopeStages.empty()) {
                prepareNextStage(0, 0.0f);
            }
            fStageDuration = 0.0f;
        }

        /**
         *
         */
        void stop() {
            fEnvelopeDone = true;
        }

        /**
         * @return time scale in seconds
         */
        float get_time_scale() {
            return fTimeScale;
        }

        /**
         * @param pTimeScale time scale in seconds
         */
        void set_time_scale(float pTimeScale) {
            fTimeScale = pTimeScale;
        }

        /**
         * @return current value
         */
        float get_current_value() {
            return fValue;
        }

        /**
         * @param pValue set current value
         */
        void set_current_value(float pValue) {
            fValue = pValue;
        }

    private:
        const float        fSampleRate;
        std::vector<Stage> fEnvelopeStages;
        float              fDelta         = 0.0f;
        int                fEnvStage      = 0;
        bool               fEnvelopeDone  = true;
        bool               fLoop          = false;
        float              fStageDuration = 0.0f;
        float              fTimeScale     = 1.0f;
        float              fValue         = 0.0f;

        float compute_delta_fraction(float pDelta, float pDuration) {
            return pDuration > 0 ? (pDelta / fSampleRate) / pDuration : pDelta;
        }

        void finished_envelope() {
            if (fLoop) {
                start();
            }
        }

        void finished_stage(int stage) {
            (void) stage;
            // TODO implement stage finished callback
        }

        void prepareNextStage(int stage, float fraction) {
            fEnvStage      = stage;
            fStageDuration = 0.0f;
            // @TODO maybe keep fractional part.
            (void) fraction;
            // @TODO but take care to also factor in the fraction when computing the delta in `setDelta`
            fValue = fEnvelopeStages[fEnvStage].value;
            if (fEnvelopeStages.size() > 1) {
                setDelta(fEnvStage);
            }
        }

        void setDelta(int pEnvStage) {
            const float mDeltaTMP = fEnvelopeStages[pEnvStage + 1].value - fEnvelopeStages[pEnvStage].value;
            fDelta                = compute_delta_fraction(mDeltaTMP, fEnvelopeStages[fEnvStage].duration);
        }
    };
} // namespace klangwellen
