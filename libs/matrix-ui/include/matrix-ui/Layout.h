#ifndef LAYOUT_H
#define LAYOUT_H

#include <string>
#include <graphics.h>

using namespace rgb_matrix;
using namespace std;

const Color DEFAULT_COLOR = Color(0, 255, 255);

class Layout {

public:
    static const string FLOAT_LEFT;
    static const string FLOAT_RIGHT;
    static const Layout FLOAT_LEFT_LAYOUT;
    static const Layout FLOAT_RIGHT_LAYOUT;

    Layout(string floating, const Color &color = DEFAULT_COLOR);

    virtual ~Layout();

    string getFloating() const;

    const Color &getColor() const;

private:
    string floating;
    const Color &color;
};


#endif /* LAYOUT_H */

