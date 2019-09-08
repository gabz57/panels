#include <matrix-ui/Layout.h>
#include <string>

const string Layout::FLOAT_LEFT = "float-left";
const string Layout::FLOAT_RIGHT = "float-right";
const Layout Layout::FLOAT_LEFT_LAYOUT = Layout(Layout::FLOAT_LEFT);
const Layout Layout::FLOAT_RIGHT_LAYOUT = Layout(Layout::FLOAT_RIGHT);

Layout::Layout(string floating, const Color &color) : floating(floating), color(color) {
}

Layout::~Layout() {
}

string Layout::getFloating() const {
    return floating;
}

const Color& Layout::getColor() const {
    return color;
}
