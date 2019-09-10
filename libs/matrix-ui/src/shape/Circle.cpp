#include <matrix-ui/shape/Circle.h>
#include <iostream>
#include <cstdlib>
#include <math.h>

const Color Circle::DEFAULT_CIRCLE_COLOR = Color(0, 255, 0);
const Layout Circle::DEFAULT_CIRCLE_LAYOUT = Layout(Floating::FLOAT_LEFT, DEFAULT_CIRCLE_COLOR);

Circle::Circle(string id, int x_center, int y_center, int radius, int x_offset, int y_offset, const Layout &layout) :
        Component(id, x_offset, y_offset, layout),
        x_center(x_center),
        y_center(y_center),
        radius(radius) {
}

Circle::~Circle() {
}

int Circle::getWidth() const {
    return 2 * radius;
}

int Circle::getHeight() const {
    return 2 * radius;
}

void Circle::draw(Canvas &canvas) {
    Canvas *preCanvas = getPreCanvas(canvas);
    const Color &color = getLayout().getColor();
    int x_cent = x_center + this->xOffset();
    int y_cent = y_center + this->yOffset();
    rgb_matrix::DrawCircle(preCanvas, x_cent, y_cent, radius, color);
    delete preCanvas;
}
