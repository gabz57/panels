#include <matrix-ui/shape/Dot.h>
#include <iostream>

using namespace std;

const Layout DEFAULT_DOT_LAYOUT = Layout(Layout::FLOAT_LEFT);

Dot::Dot(std::string id, int x, int y) :
        Component(id, 0, 0, DEFAULT_DOT_LAYOUT),
        x(x),
        y(y) {
}

Dot::Dot(std::string id, int x, int y, int x_offset, int y_offset) :
        Component(id, x_offset, y_offset, DEFAULT_DOT_LAYOUT),
        x(x),
        y(y) {
}

Dot::~Dot() {
}

int Dot::getWidth() const {
    return 1;
}

int Dot::getHeight() const {
    return 1;
}

void Dot::draw(Canvas &canvas) {
    Color color(255, 0, 0);
    canvas.SetPixel(this->xOffset() + x, this->yOffset() + y, color.r, color.g, color.b);
}
