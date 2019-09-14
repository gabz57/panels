#ifndef PANELS_PANELSLIDER_H
#define PANELS_PANELSLIDER_H

#include <list>
#include <matrix-ui/Component.h>
#include <matrix-ui/animation/AnimationComponent.h>
#include <matrix-ui/animation/transformer/PixelTransformer.h>
#include <matrix-ui/animation/transformer/base/VerticalStretchingTransformer.h>

class PanelSlider : public Component {
public:
    PanelSlider(const string &id, const list<Component *> &components, int durationMs, bool vertical = true,
                int x_offset = 0, int y_offset = 0) :
            Component(id, x_offset, y_offset, Layout::FLOAT_LEFT) {
        this->components.assign(components.begin(), components.end());
        this->currentComponent = *components.begin();
//        auto it = this->components.begin();
//        auto end = this->components.end();
//        while (it != end) {
//            Component *component = *it;
//            component->setParent(this);
//            it++;
//        }

        // Patienter x secondes
        // OPTION 1
        // - utiliser un AnimationComposant, mettre en place callback onEnd()

        int from_xy = 0;
        int to_xy = vertical ? currentComponent->getHeight() : currentComponent->getWidth();

        list<PixelTransformer *> fadeOutTransformers;
        auto verticalStretchingTransformer = new VerticalStretchingTransformer(0, 54, 50);
        fadeOutTransformers.push_back(verticalStretchingTransformer);
        currentComponentDisplay = new AnimationComponent(currentComponent, &fadeOutTransformers, 50, 1000, false);
        currentComponentDisplay->setParent(this);
//        list<PixelTransformer *> fadeInTransformers;
//        auto verticalStretchingTransformer2 = new VerticalStretchingTransformer(0, to_xy, 50, true);
//        fadeInTransformers.push_back(verticalStretchingTransformer2);
//        nextComponentDisplay = new AnimationComponent(currentComponent, &fadeInTransformers, 50, 1000, false);
    }

    void draw(Canvas &canvas) override {
        currentComponentDisplay->drawComponent(canvas);
    }

    int getWidth() const override {
        // note: we expect every components to have the same size
        return currentComponentDisplay->getWidth();
    }

    int getHeight() const override {
        // note: we expect every components to have the same size
        return currentComponentDisplay->getHeight();
    }

private:
    list<Component *> components;
    Component *currentComponent;
    Component *currentComponentDisplay;
    Component *nextComponentDisplay;
};

#endif //PANELS_PANELSLIDER_H
