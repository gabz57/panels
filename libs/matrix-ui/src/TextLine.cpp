#include "matrix-ui/TextLine.h"
#include "matrix-ui/Text.h"

TextLine::TextLine(std::string id, std::string leftTxt, std::string rightTxt, rgb_matrix::Font *font,
                   int width, int height, int x_offset, int y_offset, Layout &layout,
                   int xLeftOffset, int yLeftOffset, int xRightOffset, int yRightOffset) :
        Panel(id, width, height, x_offset, y_offset, layout) {
    this->addComponent(new Text(id + "-left", Layout::FLOAT_LEFT_LAYOUT, leftTxt, font, xLeftOffset, yLeftOffset));
    this->addComponent(new Text(id + "-right", Layout::FLOAT_RIGHT_LAYOUT, rightTxt, font, xRightOffset, yRightOffset));
}

TextLine::~TextLine() {
}
