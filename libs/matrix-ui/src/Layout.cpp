#include <matrix-ui/Layout.h>
#include <string>

const std::string Layout::FLOAT_LEFT = "float-left";
const std::string Layout::FLOAT_RIGHT = "float-right";
const Layout Layout::FLOAT_LEFT_LAYOUT = Layout(Layout::FLOAT_LEFT);
const Layout Layout::FLOAT_RIGHT_LAYOUT = Layout(Layout::FLOAT_RIGHT);

Layout::Layout(std::string floating) : floating(floating) {
}

Layout::~Layout() {
}

std::string Layout::getFloating() const {
    return this->floating;
}
