#ifndef PANELS_ANIMATIONTHREAD_H
#define PANELS_ANIMATIONTHREAD_H

#include <led-matrix.h>
#include <thread.h>
#include <list>
#include <matrix-ui/animation/LocalTime.h>
#include <matrix-ui/animation/transformer/PixelTransformer.h>

class AnimationThread : public Thread {
public:
    AnimationThread(Mutex *animation_mutex, std::list<PixelTransformer *> *transformers, int nbSteps,
                    tmillis_t *duration_ms, bool infiniteLoop = false, tus_t initialClockCompensation = 0) :
            animation_mutex_(animation_mutex),
            transformers(transformers),
            nbSteps(nbSteps),
            duration_ms(duration_ms),
            infiniteLoop(infiniteLoop),
            initialClockCompensation(initialClockCompensation),
            running_(false) {
    }

    virtual void Start(int realtime_priority = 0, uint32_t affinity_mask = 0) {
        MutexLock l(animation_mutex_);
        if (!running_) {
            running_ = true;
            if (*duration_ms > 0) {
                Thread::Start(realtime_priority, affinity_mask);
            } else {
                for (int i = 0; i < nbSteps; ++i) {
                    for (PixelTransformer *transformer : *transformers) {
                        transformer->Step();
                    }
                }
                running_ = false;
            }
        }
    }

    void Stop() {
        MutexLock l(animation_mutex_);
        running_ = false;
    }

    bool running() {
        MutexLock l(animation_mutex_);
        return running_;
    }

    virtual void Run() {
        int animation_count = 0;
        const tus_t loop_duration_us = *duration_ms * 1000;
        const tus_t frame_duration_us = loop_duration_us / nbSteps;

        MutexLock *m;
        tus_t all_start_time = GetTimeInMicros();
        tus_t for_loop_start_time;
        tus_t for_loop_sleep_correction = 0;
        tus_t while_loop_start_time;
        tus_t while_loop_sleep_correction = 0;
        while (!interrupt_received && running() && (infiniteLoop || animation_count <= 0)) {
            while_loop_start_time = GetTimeInMicros();
            if (animation_count > 0) {
                for (PixelTransformer *transformer : *transformers) {
                    transformer->Reset();
                }
            }
            int nbStepToAdvanceFirstTimeOnly = (int) (initialClockCompensation / (long long) frame_duration_us);
            int step = animation_count > 0 ? 0 : nbStepToAdvanceFirstTimeOnly;
            for (; step < nbSteps; step++) {
                for_loop_start_time = GetTimeInMicros();
                if (!running() || interrupt_received) break;
                m = new MutexLock(animation_mutex_);
                for (PixelTransformer *transformer : *transformers) {
                    transformer->Step();
                }
                delete m;
                SleepUs(frame_duration_us - (GetTimeInMicros() - for_loop_start_time) - for_loop_sleep_correction);
                for_loop_sleep_correction = computeCorrectionSince(all_start_time,
                                                                   animation_count * (loop_duration_us) +
                                                                   frame_duration_us * (step + 1)
                                                                   - initialClockCompensation);
            }
            animation_count++;
            if (interrupt_received) break;
            SleepUs(loop_duration_us - (GetTimeInMicros() - while_loop_start_time) - while_loop_sleep_correction
                    - (animation_count > 1 ? 0 : initialClockCompensation));
            while_loop_sleep_correction = computeCorrectionSince(all_start_time, animation_count * (loop_duration_us)
                                                                                 - initialClockCompensation);
            if (animation_count == INT_MAX) {
                animation_count = 0;
                all_start_time = GetTimeInMicros();
            }
        }
        Stop();
    }

private:
    inline tus_t computeCorrectionSince(tus_t start_time, tus_t computed_elapsed) const {
        tus_t elapsed = GetTimeInMicros() - start_time;
        tus_t sleep_correction = elapsed - computed_elapsed;
        return sleep_correction;
    };

    Mutex *animation_mutex_;
    std::list<PixelTransformer *> *transformers;
    tmillis_t *duration_ms;
    tus_t initialClockCompensation;
    int nbSteps;
    bool infiniteLoop;
    bool running_;
};

#endif //PANELS_ANIMATIONTHREAD_H
