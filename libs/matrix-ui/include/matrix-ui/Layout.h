#ifndef LAYOUT_H
#define LAYOUT_H

#include <string>
#include <list>
#include <graphics.h>
#include <matrix-ui/animation/transformer/PixelTransformer.h>

using namespace rgb_matrix;
using namespace std;

const Color DEFAULT_COLOR = Color(0, 255, 255);

enum class Floating {
    FLOAT_LEFT,
    FLOAT_RIGHT
};

class Layout {

public:
    static const Layout FLOAT_LEFT;
    static const Layout FLOAT_RIGHT;

    Layout(const Floating &floating, const Color &color = DEFAULT_COLOR);

    Layout(const Layout &layout, const std::list<PixelTransformer *> &tr);

    virtual ~Layout();

    const Floating &getFloating() const;

    const Color &getColor() const;
    void setColor(const Color &color);

    const list<PixelTransformer *> &getTransformers() const;

private:
//    void setTransformers(const list<PixelTransformer *> &transformers);

    list<PixelTransformer *> transformers;
    const Floating floating;
    Color color;
};


#endif /* LAYOUT_H */

