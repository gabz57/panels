#include <Component.h>

using namespace rgb_matrix;

Component::Component(std::string id, int x_offset, int y_offset, Layout &layout) :
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

std::string Component::getId() const {
    return this->id;
}

int Component::xOffset() const {
    return this->x_offset;
}

int Component::yOffset() const {
    return this->y_offset;
}

Layout &Component::getLayout() const {
    return this->layout;
}
