#include <Text.h>
#include <iostream>
#include <stdlib.h>
#include "utf8-internal.h"

Text::Text(std::string id, Layout &layout, std::string text, rgb_matrix::Font &font) :
        Component(id, 0, 0, layout),
        text(text),
        font(font) {
}

Text::Text(std::string id, Layout &layout, std::string text, rgb_matrix::Font &font, int x_offset, int y_offset) :
        Component(id, x_offset, y_offset, layout),
        text(text),
        font(font) {
}

Text::~Text() {
}

int Text::getWidth() const {
    int width = 0;
    const char *utf8_text = this->text.c_str();
    for (const char &c : this->text) {
        const uint32_t cp = utf8_next_codepoint(utf8_text);
        int charWidth = font.CharacterWidth(cp);
        std::cout << "Text::getCharWidth :: " << c << " = " << charWidth << std::endl;
        width += charWidth;
    }
    std::cout << "Text::getWidth :: " << this->text << " = " << width << std::endl;
    return width;
}

int Text::getHeight() const {
    return font.height();
}

void Text::draw(rgb_matrix::Canvas &canvas, const Component *parent) const {
    std::cout << "Drawing Text :: " << this->text << std::endl;

    Color color(255, 255, 0);
    Color bg_color(0, 0, 0);

    int letter_spacing = 0;
    const int x = this->getLayout().getFloating() == Layout::FLOAT_LEFT
                  ? this->xOffset()
                  : this->xOffset() + parent->getWidth() - getWidth();
    int y = this->yOffset();
    rgb_matrix::DrawText(&canvas, font, x, y + font.baseline(), color, &bg_color, this->text.c_str(), letter_spacing);
}