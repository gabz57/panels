#include <matrix-ui/shape/Dot.h>
#include <iostream>

const Color Dot::DEFAULT_DOT_COLOR = Color(255, 0, 0);
const Layout Dot::DEFAULT_DOT_LAYOUT = Layout(Floating::FLOAT_LEFT, DEFAULT_DOT_COLOR);

Dot::Dot(const string &id, int x, int y, int x_offset, int y_offset, const Layout &layout) :
        Component(id, x_offset, y_offset, layout),
        x(x),
        y(y) {
}

Dot::Dot(Dot *source, const string &id, const Layout &layout) :
        Component(id, source->x_offset, source->y_offset, layout),
        x(source->x),
        y(source->y) {
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
    const Color &color = getLayout().getColor();
    canvas.SetPixel(this->xOffset() + x, this->yOffset() + y, color.r, color.g, color.b);
}
