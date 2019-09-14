#include <matrix-ui/Layout.h>

const Layout Layout::FLOAT_LEFT = Layout(Floating::FLOAT_LEFT);
const Layout Layout::FLOAT_RIGHT = Layout(Floating::FLOAT_RIGHT);

Layout::Layout(const Floating &floating, const Color &color, PixelTransformer *pixelTransformer) :
        floating(floating),
        color(color) {
    if (pixelTransformer != nullptr) {
        this->transformers.push_back(pixelTransformer);
    }
}

Layout::Layout(const Layout &layout, const std::list<PixelTransformer *> &tr) :
        floating(layout.floating),
        color(layout.color) {
    this->transformers.assign(tr.begin(), tr.end());
}

Layout::Layout(const Layout &layout, PixelTransformer *pixelTransformer) :
        floating(layout.floating),
        color(layout.color) {
    if (pixelTransformer != nullptr) {
        this->transformers.push_back(pixelTransformer);
    }}

Layout::~Layout() {
    while (!transformers.empty()) {
        delete transformers.front(), transformers.pop_front();
    }
}

const Floating &Layout::getFloating() const {
    return floating;
}

const Color &Layout::getColor() const {
    return color;
}

void Layout::setColor(const Color &color) {
    this->color = color;
}

const list<PixelTransformer *> &Layout::getTransformers() const {
    return transformers;
}
