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
                    tmillis_t *duration_ms, bool infiniteLoop = false) :
            animation_mutex_(animation_mutex),
            transformers(transformers),
            nbSteps(nbSteps),
            duration_ms(duration_ms),
            infiniteLoop(infiniteLoop),
            running_(false) {
    }

    virtual void Start(int realtime_priority = 0, uint32_t affinity_mask = 0) {
        {
            MutexLock l(animation_mutex_);
            running_ = true;
        }
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

    void Stop() {
        MutexLock l(animation_mutex_);
        running_ = false;
        cout << "Animation Thread STOPPED" << endl;
    }

    bool running() {
        MutexLock l(animation_mutex_);
        return running_;
    }

    virtual void Run() {
        const tmillis_t anim_delay_ms = *duration_ms / nbSteps;
        cout << "Animation Thread STARTED" << endl;
        tmillis_t start_ms = GetTimeInMillis();

        bool once = false;
        while (infiniteLoop || !once) {
            for (PixelTransformer *transformer : *transformers) {
                transformer->Reset();
            }
            if (interrupt_received) break;
            for (int i = 0; i < nbSteps; ++i) {
                if (interrupt_received) break;

                MutexLock *m = new MutexLock(animation_mutex_);

                for (PixelTransformer *transformer : *transformers) {
                    //                cout << "Stepping" << endl;
                    transformer->Step();
                }
                delete m;// release animation Lock to allow drawing methods
                SleepMillis(anim_delay_ms);

            }
            once = true;
        }
//        while (running() && !interrupt_received && (GetTimeInMillis() - start_ms)<= *duration_ms) {
////            tmillis_t start_wait_ms = GetTimeInMillis();
//            MutexLock *m = new MutexLock(animation_mutex_);
//
//            for (PixelTransformer *transformer : *transformers) {
////                cout << "Stepping" << endl;
//                transformer->Step();
//            }
//            delete m;// release animation Lock to allow drawing methods
////            tmillis_t time_already_spent = GetTimeInMillis() - start_wait_ms;
//
////            SleepMillis(anim_delay_ms - time_already_spent);
//            SleepMillis(anim_delay_ms);
//        }
        Stop();
    };

private:
    Mutex *animation_mutex_;
    std::list<PixelTransformer *> *transformers;
    tmillis_t *duration_ms;
    int nbSteps;
    bool infiniteLoop;
    bool running_;
};

#endif //PANELS_ANIMATIONTHREAD_H
