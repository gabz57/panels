#include <matrix-ui/Layout.h>

const Layout Layout::FLOAT_LEFT = Layout(Floating::FLOAT_LEFT);
const Layout Layout::FLOAT_RIGHT = Layout(Floating::FLOAT_RIGHT);

Layout::Layout(const Floating &floating, const Color &color) : floating(floating), color(color) {
}

Layout::Layout(const Layout &layout, const std::list<PixelTransformer *> &tr) :
        floating(layout.floating),
        color(layout.color) {
    this->transformers.assign(tr.begin(), tr.end());
}

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

const list<PixelTransformer *> &Layout::getTransformers() const {
    return transformers;
}

//void Layout::setTransformers(const list<PixelTransformer *> &new_transformers) {
//    this->transformers.assign(new_transformers.cbegin(), new_transformers.cend());
//}
