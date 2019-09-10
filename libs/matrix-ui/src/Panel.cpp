#include <matrix-ui/Panel.h>
#include <iostream>

Panel::Panel(const string& id, int width, int height, int x_offset, int y_offset, const Layout &layout)
        : Component(id, x_offset, y_offset, layout), width(width), height(height) {
}

Panel::~Panel() {
    auto it = this->components.begin();
    auto end = this->components.end();
    while (it != end) {
        delete it->second;
        it->second = nullptr;
        it++;
    }
}

int Panel::getWidth() const {
    return this->width;
}

int Panel::getHeight() const {
    return this->height;
}

const std::unordered_map<std::string, Component *> *Panel::getComponents() {
    return &components;
}

void Panel::addComponent(Component *component) {
    // todo ensure fit inside width & height or print message + return 1
    component->setParent(this);
    this->components.insert(std::make_pair(component->getId(), component));
}

void Panel::draw(Canvas &canvas) {
    Canvas *preCanvas = getPreCanvas(canvas);

    std::unordered_map<std::string, Component *> mp = this->components;
    auto it = mp.begin();
    while (it != this->components.end()) {
        it->second->draw(*preCanvas);
        it++;
    }
    delete preCanvas;
}