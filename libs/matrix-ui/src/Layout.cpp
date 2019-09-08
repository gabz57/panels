#include <matrix-ui/Layout.h>

const Layout Layout::FLOAT_LEFT = Layout(Floating::FLOAT_LEFT);
const Layout Layout::FLOAT_RIGHT = Layout(Floating::FLOAT_RIGHT);

Layout::Layout(const Floating &floating, const Color &color) : floating(floating), color(color) {
}

Layout::~Layout() {
}

const Floating &Layout::getFloating() const {
    return floating;
}

const Color &Layout::getColor() const {
    return color;
}
