#include <Layout.h>
#include <string>

const std::string Layout::FLOAT_LEFT = "float-left";
const std::string Layout::FLOAT_RIGHT = "float-right";

Layout::Layout(std::string floating) : floating(floating) {
}

Layout::~Layout() {
}

std::string Layout::getFloating() const {
    return this->floating;
}
