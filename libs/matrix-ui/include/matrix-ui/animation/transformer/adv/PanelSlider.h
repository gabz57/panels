#ifndef PANELS_PANELSLIDER_H
#define PANELS_PANELSLIDER_H

#include <list>
#include <matrix-ui/Component.h>

class PanelSlider : public Component {
public:
    PanelSlider(const string &id, const list<Component *> &components, int durationMs,
                int x_offset = 0, int y_offset = 0) :
            Component(id, x_offset, y_offset, Layout::FLOAT_LEFT) {
        this->components.assign(components.begin(), components.end());
        this->currentComponent = *components.begin();
        auto it = this->components.begin();
        auto end = this->components.end();
        while (it != end) {
            Component *component = *it;
            component->setParent(this);
            it++;
        }
    }

    void draw(Canvas &canvas) override {
        currentComponent->drawComponent(canvas);
    }

    int getWidth() const override {
        // note: we expect every components to have the same size
        return currentComponent->getWidth();
    }

    int getHeight() const override {
        // note: we expect every components to have the same size
        return currentComponent->getHeight();
    }

private:
    list<Component *> components;
    Component *currentComponent;
};

#endif //PANELS_PANELSLIDER_H
