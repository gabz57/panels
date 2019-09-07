#ifndef PANELS_ANIMATIONCOMPONENT_H
#define PANELS_ANIMATIONCOMPONENT_H

#include "canvas.h"
#include "matrix-ui/CanvasHolder.h"
#include "matrix-ui/Layout.h"

static Layout DEFAULT_ANIMATION_LAYOUT = Layout(Layout::FLOAT_LEFT);

class AnimationComponent : public Component {
public:
    AnimationComponent(Component *component, PixelTransformer *transformer, uint8_t duration_ms) :
            Component(component->getId() + "-anim", 0, 0, DEFAULT_ANIMATION_LAYOUT),
            delegate(component),
            duration_ms(duration_ms) {
        this->transformers.push_back(transformer);
    }

    AnimationComponent(Component *component, std::list<PixelTransformer *> transformers, uint8_t duration_ms) :
            Component(component->getId() + "-anim", 0, 0, DEFAULT_ANIMATION_LAYOUT),
            delegate(component),
            duration_ms(duration_ms) {
        this->transformers.assign(transformers.begin(), transformers.end());
    }

    virtual ~AnimationComponent() {
        while (!transformers.empty()) {
            delete transformers.front(), transformers.pop_front();
        }
    }

    virtual void draw(CanvasHolder &canvasHandler) {
        draw(*canvasHandler.getCanvas());
    }

    void draw(Canvas &canvas) {
        Canvas *canvasAdapter = new CanvasAdapter(this, &canvas, transformers);
        delegate->draw(*canvasAdapter);
        delete canvasAdapter;
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
    uint8_t duration_ms;
};

#endif //PANELS_ANIMATIONCOMPONENT_H
