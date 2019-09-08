#ifndef LAYOUT_H
#define LAYOUT_H

#include <string>
#include <graphics.h>

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

    virtual ~Layout();

    const Floating &getFloating() const;

    const Color &getColor() const;

private:
    Floating floating;
    const Color &color;
};


#endif /* LAYOUT_H */

