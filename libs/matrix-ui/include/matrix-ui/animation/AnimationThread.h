#ifndef PANELS_ANIMATIONTHREAD_H
#define PANELS_ANIMATIONTHREAD_H

#include <led-matrix.h>
#include <thread.h>
#include <matrix-ui/animation/LocalTime.h>
#include <matrix-ui/animation/transformer/PixelTransformer.h>

class AnimationThread : public Thread {
public:
    AnimationThread(Mutex *animation_mutex, std::list<PixelTransformer *> *transformers, int nbSteps, tmillis_t *duration_ms) :
            animation_mutex_(animation_mutex),
            transformers(transformers),
            duration_ms(duration_ms),
            nbSteps(nbSteps),
            running_(false) {
    }

    virtual void Start(int realtime_priority=0, uint32_t affinity_mask=0) {
        {
            MutexLock l(animation_mutex_);
            running_ = true;
        }
        Thread::Start(realtime_priority, affinity_mask);
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
        tmillis_t anim_delay_ms = *duration_ms / nbSteps;
        cout << "Animation Thread STARTED" << endl;
        tmillis_t start_ms = GetTimeInMillis();

        while (running() && /*!interrupt_received && */ (GetTimeInMillis() - start_ms)<= *duration_ms) {
//            tmillis_t start_wait_ms = GetTimeInMillis();
            MutexLock *m = new MutexLock(animation_mutex_);

            for (PixelTransformer *transformer : *transformers) {
                cout << "Stepping" << endl;
                transformer->Step();
            }
            delete m;// release animation Lock to allow drawing methods
//            tmillis_t time_already_spent = GetTimeInMillis() - start_wait_ms;

//            SleepMillis(anim_delay_ms - time_already_spent);
            SleepMillis(anim_delay_ms);
        }
        Stop();
    };

private:
    Mutex *animation_mutex_;
    std::list<PixelTransformer *> *transformers;
    tmillis_t *duration_ms;
    int nbSteps;
    bool running_;
};

#endif //PANELS_ANIMATIONTHREAD_H
