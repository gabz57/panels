#include "matrix-ui/RootPanel.h"
#include <iostream>

Layout DEFAULT_LAYOUT = Layout(Layout::FLOAT_LEFT);

RootPanel::RootPanel(std::string id, int width, int height, Component *childComponent) :
        Component(id, 0, 0, DEFAULT_LAYOUT),
        width(width),
        height(height),
        childComponent(childComponent) {
    childComponent->setParent(this);
}

RootPanel::~RootPanel() {
    delete childComponent;
}

void RootPanel::draw(Canvas &canvas) {
    std::cout << std::endl<< std::endl<< "Drawing RootPanel :: " << this->getId()
              << " - w:" << this->width << ", h:" << this->height
              << std::endl;
    this->childComponent->draw(canvas);
}

int RootPanel::getWidth() const {
    return this->width;
}

int RootPanel::getHeight() const {
    return this->height;
}
