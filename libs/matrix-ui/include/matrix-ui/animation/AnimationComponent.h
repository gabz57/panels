#ifndef PANELS_ANIMATIONCOMPONENT_H
#define PANELS_ANIMATIONCOMPONENT_H

#include "canvas.h"
#include "LocalTime.h"
#include "matrix-ui/CanvasHolder.h"
#include "matrix-ui/Layout.h"
#include "matrix-ui/animation/AnimationThread.h"
#include "matrix-ui/animation/CanvasAdapter.h"
#include "matrix-ui/animation/transformer/adv/AnimationEndListener.h"
#include "matrix-ui/dp/Observee.h"
#include "matrix-ui/dp/Observer.h"

static Layout DEFAULT_ANIMATION_LAYOUT = Layout(Floating::FLOAT_LEFT);

class AnimationThreadEndObserver : public Observer {
public:
    explicit AnimationThreadEndObserver(const AnimationEndListener &animationEndListener) :
            animationEndListener(animationEndListener) {}

    ~AnimationThreadEndObserver() override = default;

    void Notify(Observee *observee) override {
        this->animationEndListener.onEnd();
    };

private:
    const AnimationEndListener &animationEndListener;
};

class AnimationComponent : public Component, public AnimationEndListener {
public:
    AnimationComponent(Component *component, PixelTransformer *transformer, int nbSteps, tmillis_t duration_ms,
                       bool infiniteLoop = false, tus_t initialClockCompensation = 0, int x_offset = 0,
                       int y_offset = 0) :
            Component(component->getId() + "-anim", x_offset, y_offset, DEFAULT_ANIMATION_LAYOUT),
            delegate(component),
            duration_ms(duration_ms),
            nbSteps(nbSteps) {
        this->transformers.push_back(transformer);
        this->animationThread = new AnimationThread(&this->animation_mutex_, &this->transformers, this->nbSteps,
                                                    &this->duration_ms, infiniteLoop, initialClockCompensation);
        animationThreadEndObserver = new AnimationThreadEndObserver(*this);
        animationThread->AddObserver(animationThreadEndObserver);
        this->started = false;
        component->setParent(this);
    }

    AnimationComponent(Component *component, std::list<PixelTransformer *> *transformers, int nbSteps,
                       tmillis_t duration_ms, bool infiniteLoop = false, tus_t initialClockCompensation = 0,
                       int x_offset = 0, int y_offset = 0) :
            Component(component->getId() + "-anim", x_offset, y_offset, DEFAULT_ANIMATION_LAYOUT),
            delegate(component),
            duration_ms(duration_ms),
            nbSteps(nbSteps) {
        this->transformers.assign(transformers->begin(), transformers->end());
        animationThread = new AnimationThread(&this->animation_mutex_, &this->transformers, this->nbSteps,
                                              &this->duration_ms, infiniteLoop, initialClockCompensation);
        animationThreadEndObserver = new AnimationThreadEndObserver(*this);
        animationThread->AddObserver(animationThreadEndObserver);
        started = false;
        component->setParent(this);
    }

    virtual ~AnimationComponent() {
        delete animationThreadEndObserver;
        while (!transformers.empty()) {
            delete transformers.front(), transformers.pop_front();
        }
        delete animationThread;
    }

    void draw(Canvas &canvas) {
        if (!started) {
            started = true;
            // let transformers being modified to animate at next drawing
            animationThread->Start();
            cout << "started : " << this->delegate->getId();
            cout << endl;
        }
        MutexLock lock(&animation_mutex_);
        CanvasAdapter canvasAdapter = CanvasAdapter(&canvas, transformers);
        delegate->drawComponent(canvasAdapter);
    };

    void onEnd() const {
        cout << "ended : " << this->delegate->getId();
        cout << endl;
    }

    virtual int getWidth() const {
        return delegate->getWidth();
    };

    virtual int getHeight() const {
        return delegate->getHeight();
    };

private:
    Component *delegate;
    std::list<PixelTransformer *> transformers;
    tmillis_t duration_ms;
    Mutex animation_mutex_;
    int nbSteps;
    AnimationThread *animationThread;
    bool started;
    AnimationThreadEndObserver *animationThreadEndObserver;
};


#endif //PANELS_ANIMATIONCOMPONENT_H
