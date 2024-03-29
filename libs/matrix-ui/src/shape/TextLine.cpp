#include "matrix-ui/shape/TextLine.h"
#include "matrix-ui/shape/Text.h"

const Color TextLine::DEFAULT_TEXTLINE_COLOR = Color(255, 0, 255);
const Layout TextLine::DEFAULT_TEXTLINE_LAYOUT = Layout(Floating::FLOAT_LEFT, DEFAULT_TEXTLINE_COLOR);

TextLine::TextLine(const string& id, const string& leftTxt, const string& rightTxt, const rgb_matrix::Font *font,
                   int width, int height, int x_offset, int y_offset, const Layout &layout,
                   int xLeftOffset, int yLeftOffset, int xRightOffset, int yRightOffset) :
        Panel(id, width, height, x_offset, y_offset, layout) {
    this->addComponent(new Text(id + "-left", leftTxt, font, Layout::FLOAT_LEFT, xLeftOffset, yLeftOffset));
    this->addComponent(new Text(id + "-right", rightTxt, font, Layout::FLOAT_RIGHT, xRightOffset, yRightOffset));
}

TextLine::~TextLine() {
}
