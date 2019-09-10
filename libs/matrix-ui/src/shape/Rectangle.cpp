#include <matrix-ui/shape/Rectangle.h>
#include <iostream>

const Color Rectangle::DEFAULT_RECTANGLE_COLOR = Color(255, 0, 0);
const Layout Rectangle::DEFAULT_RECTANGLE_LAYOUT = Layout(Floating::FLOAT_LEFT, DEFAULT_RECTANGLE_COLOR);

Rectangle::Rectangle(const string& id, int x, int y, int width, int height, int x_offset, int y_offset, const Layout &layout) :
        Component(id, x_offset, y_offset, layout),
        x(x), y(y), width(width), height(height) {
}

Rectangle::Rectangle(Rectangle *source, const string& id, const Layout &layout) :
        Component(id, source->x_offset, source->y_offset, layout),
        x(source->x), y(source->y), width(source->width), height(source->height) {
}

Rectangle::~Rectangle() {
}

int Rectangle::getWidth() const {
    return width;
}

int Rectangle::getHeight() const {
    return height;
}

void Rectangle::draw(Canvas &canvas) {
    // FIXME: poor style that does the trick for 'Rectangle',
    //  should find a design to apply Component.layout.transformers at every level transparently
    Canvas *preCanvas = getPreCanvas(canvas);
    int x_start = this->x + xOffset();
    int x_end = x_start + width;
    int y_start = this->y + yOffset();
    int y_end = y_start + height;
    const Color &color = getLayout().getColor();

    for (int x_ = x_start; x_ < x_end; x_++) {
        preCanvas->SetPixel(x_, y_start, color.r, color.g, color.b);
        preCanvas->SetPixel(x_, y_end - 1, color.r, color.g, color.b);
    }
    for (int y_ = y_start; y_ < y_end; y_++) {
        preCanvas->SetPixel(x_start, y_, color.r, color.g, color.b);
        preCanvas->SetPixel(x_end - 1, y_, color.r, color.g, color.b);
    }
    delete preCanvas;
}