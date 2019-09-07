#include <matrix-ui/Text.h>
#include <iostream>
#include "utf8-internal.h"

Text::Text(std::string id, std::string text, const rgb_matrix::Font *font, const Layout &layout) :
        Component(id, 0, 0, layout),
        text(text),
        font(font) {
}

Text::Text(std::string id, std::string text, const rgb_matrix::Font *font, const Layout &layout, int x_offset,
           int y_offset) :
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
        int charWidth = font->CharacterWidth(cp);
//        std::cout << "Text::getCharWidth :: " << c << " = " << charWidth << std::endl;
        width += charWidth;
    }
//    std::cout << "Text::getWidth :: " << this->text << " = " << width << std::endl;
    return width;
}

int Text::getHeight() const {
    return font->height();
}

void Text::draw(Canvas &canvas) {
 //   std::cout << "Drawing Text :: " << this->getId() << " - " << this->text << std::endl;

    Color color(0, 0, 255);
    Color bg_color(0, 0, 0);

    int letter_spacing = 0;

    int x = this->xOffset();
    int y = this->yOffset();

    // Apply layout
    x += this->getLayout().getFloating() == Layout::FLOAT_LEFT
         ? 0
         : this->getParent()->getWidth() - getWidth();

//    std::cout << "Drawing Text :: " << this->getId() << " - " << this->text
//    std::cout << " pos(" << x << "," << y << ") "
//              << " offset(" << this->xOffset() << "," << this->yOffset() << ") "
//              << std::endl;

    rgb_matrix::DrawText(&canvas, *font, x, y + font->baseline(), color, &bg_color, this->text.c_str(), letter_spacing);
}
