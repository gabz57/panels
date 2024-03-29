#include <matrix-ui/Component.h>
#include "matrix-ui/animation/CanvasAdapter.h"

using namespace rgb_matrix;

Component::Component(const string &id, int x_offset, int y_offset, const Layout &layout) :
        id(id),
        x_offset(x_offset),
        y_offset(y_offset),
        layout(layout) {
}

Component::~Component() {
}

bool Component::operator==(const Component &other) {
    return this->id == other.id;
}

void Component::setParent(const Component *parentComponent) {
    this->parent = parentComponent;
}

const Component *Component::getParent() const {
    return this->parent;
}

string Component::getId() const {
    return this->id;
}

int Component::xOffset() const {
    if (this->parent != nullptr) {
        return this->parent->xOffset() + this->x_offset;
    }
    return this->x_offset;
}

int Component::yOffset() const {
    if (this->parent != nullptr) {
        return this->parent->yOffset() + this->y_offset;
    }
    return this->y_offset;
}

Layout &Component::getLayout() {
    return this->layout;
}

Canvas *Component::canvasAdapter(Canvas &canvas) {
    return new CanvasAdapter(&canvas, layout.getTransformers());
}

