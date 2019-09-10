#include "matrix-ui/RootPanel.h"
#include <iostream>

using namespace std;

Layout DEFAULT_LAYOUT = Layout(Floating::FLOAT_LEFT);

RootPanel::RootPanel(const string &id, int width, int height, CanvasHolder &canvasHandler, Component *childComponent) :
        Component(id, 0, 0, DEFAULT_LAYOUT),
        width(width),
        height(height),
        canvasHandler(canvasHandler),
        childComponent(childComponent) {
    childComponent->setParent(this);
}

RootPanel::~RootPanel() {
    delete childComponent;
}

void RootPanel::render() {
    canvasHandler.clear();
    this->draw(*canvasHandler.getCanvas());
    canvasHandler.renderAndSwap();
}

void RootPanel::draw(Canvas &canvas) {
    this->childComponent->drawComponent(*canvasAdapter(canvas));
}

int RootPanel::getWidth() const {
    return this->width;
}

int RootPanel::getHeight() const {
    return this->height;
}
