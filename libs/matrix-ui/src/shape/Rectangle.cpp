#include <matrix-ui/shape/Rectangle.h>

const Color Rectangle::DEFAULT_RECTANGLE_COLOR = Color(255, 0, 0);
const Layout Rectangle::DEFAULT_RECTANGLE_LAYOUT = Layout(Floating::FLOAT_LEFT, DEFAULT_RECTANGLE_COLOR);

Rectangle::Rectangle(string id, int x, int y, int width, int height, int x_offset, int y_offset, const Layout &layout) :
        Component(id, x_offset, y_offset, layout),
        x(x), y(y), width(width), height(height) {
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
    int x_start = this->x + xOffset();
    int x_end = x_start + width;
    int y_start = this->y + yOffset();
    int y_end = y_start + height;
    const Color &color = getLayout().getColor();

    for (int x_ = x_start; x_ < x_end; x_++) {
        canvas.SetPixel(x_, y_start, color.r, color.g, color.b);
        canvas.SetPixel(x_, y_end - 1, color.r, color.g, color.b);
    }
    for (int y_ = y_start; y_ < y_end; y_++) {
        canvas.SetPixel(x_start, y_, color.r, color.g, color.b);
        canvas.SetPixel(x_end -1, y_, color.r, color.g, color.b);
    }
}