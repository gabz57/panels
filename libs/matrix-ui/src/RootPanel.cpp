#include "matrix-ui/RootPanel.h"
#include <iostream>

using namespace std;

Layout DEFAULT_LAYOUT = Layout(Layout::FLOAT_LEFT);

RootPanel::RootPanel(string id, int width, int height, CanvasHolder &canvasHandler, Component *childComponent) :
        Component(id, 0, 0, DEFAULT_LAYOUT),
        width(width),
        height(height),
        _canvasHandler(canvasHandler),
        childComponent(childComponent) {
    childComponent->setParent(this);
}

RootPanel::~RootPanel() {
    delete childComponent;
}

void RootPanel::render() {
//    cout << "RootPanel::render" << endl;
    _canvasHandler.clear();
    this->draw(_canvasHandler);
    _canvasHandler.renderAndSwap();
}

void RootPanel::draw(Canvas &canvas) {
    draw(_canvasHandler);
}

void RootPanel::draw(CanvasHolder &canvasHandler) {
//    cout << endl << "Drawing RootPanel :: " << this->getId()
//              << " - w:" << this->width << ", h:" << this->height
//              << endl;
    this->childComponent->draw(canvasHandler);
}

int RootPanel::getWidth() const {
    return this->width;
}

int RootPanel::getHeight() const {
    return this->height;
}
