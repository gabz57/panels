#include <matrix-ui/Line.h>
#include <iostream>
#include <cstdlib>

using namespace std;

const Layout DEFAULT_LINE_LAYOUT = Layout(Layout::FLOAT_LEFT);

Line::Line(std::string id, int x_start, int y_start, int x_end, int y_end) :
        Component(id, 0, 0, DEFAULT_LINE_LAYOUT),
        x_start(x_start),
        y_start(y_start),
        x_end(x_end),
        y_end(y_end) {
}

Line::Line(std::string id, int x_start, int y_start, int x_end, int y_end, int x_offset, int y_offset) :
        Component(id, x_offset, y_offset, DEFAULT_LINE_LAYOUT),
        x_start(x_start),
        y_start(y_start),
        x_end(x_end),
        y_end(y_end) {
}

Line::~Line() {
}

int Line::getWidth() const {
    return abs(x_end - x_start);
}

int Line::getHeight() const {
    return abs(y_end - y_start);
}

void Line::draw(Canvas &canvas) {
    Color color(255, 0, 0);
    int x = this->xOffset();
    int y = this->yOffset();
    rgb_matrix::DrawLine(&canvas, x + x_start, y + y_start, x + x_end, y + y_end, color);
}
