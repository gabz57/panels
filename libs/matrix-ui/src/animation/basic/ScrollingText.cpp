#include <matrix-ui/animation/basic/ScrollingText.h>
#include <matrix-ui/animation/transformer/TranslatonTransformer.h>

ScrollingText::ScrollingText(std::string id, RGBMatrix *matrix,
                             std::string text, const rgb_matrix::Font *font,
                             int x_offset, int y_offset,
                             const Layout &layout) :
        AnimatedComponent(id + "-animation", matrix, x_offset, y_offset, Layout::FLOAT_LEFT_LAYOUT),
        text(Text(id + "-text", text, font, layout, 0, 0)) {
    this->text.setParent(this);
    // TODO: enhance values, or allow passing x & y by constructor
    this->transformers.push_back(new TranslationTransformer(-100));
}

ScrollingText::~ScrollingText() {
}

int ScrollingText::getWidth() const {
    return this->text.getWidth();
}

int ScrollingText::getHeight() const {
    return this->text.getHeight();
}

void ScrollingText::drawNextFrame(CanvasHolder &canvasHandler, uint32_t *delay_us) {
    this->text.draw(canvasHandler);
    delete delay_us;
    // TODO: enhance values, or allow passing delay_us by constructor
    *delay_us = 1000;
}
