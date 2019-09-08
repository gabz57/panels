#ifndef PANELS_ANIMATIONCOMPONENT_H
#define PANELS_ANIMATIONCOMPONENT_H

#include "canvas.h"
#include "LocalTime.h"
#include "matrix-ui/CanvasHolder.h"
#include "matrix-ui/Layout.h"
#include "matrix-ui/animation/AnimationThread.h"
#include "matrix-ui/animation/CanvasAdapter.h"

static Layout DEFAULT_ANIMATION_LAYOUT = Layout(Layout::FLOAT_LEFT);

class AnimationComponent : public Component {
public:
    AnimationComponent(Component *component, PixelTransformer *transformer, int nbSteps, tmillis_t duration_ms, int x_offset = 0, int y_offset = 0) :
            Component(component->getId() + "-anim",  x_offset, y_offset, DEFAULT_ANIMATION_LAYOUT),
            delegate(component),
            duration_ms(duration_ms),
            nbSteps(nbSteps) {
        this->transformers.push_back(transformer);
        this->animationThread = new AnimationThread(&this->animation_mutex_, &this->transformers, this->nbSteps,
                                                    &this->duration_ms);
        this->started = false;
        component->setParent(this);
    }

    AnimationComponent(Component *component, std::list<PixelTransformer *> *transformers, int nbSteps,
                       tmillis_t duration_ms, int x_offset = 0, int y_offset = 0) :
            Component(component->getId() + "-anim", x_offset, y_offset, DEFAULT_ANIMATION_LAYOUT),
            delegate(component),
            duration_ms(duration_ms),
            nbSteps(nbSteps) {
        this->transformers.assign(transformers->begin(), transformers->end());
        animationThread = new AnimationThread(&this->animation_mutex_, &this->transformers, this->nbSteps,
                                              &this->duration_ms);
        started = false;
        component->setParent(this);
    }

    virtual ~AnimationComponent() {
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
        }
        MutexLock lock(&animation_mutex_);
        CanvasAdapter canvasAdapter = CanvasAdapter(&canvas, transformers);
        delegate->draw(canvasAdapter);
    };

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
};

#endif //PANELS_ANIMATIONCOMPONENT_H
