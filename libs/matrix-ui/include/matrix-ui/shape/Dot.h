#ifndef DOT_H
#define DOT_H

#include <string>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Layout.h>
#include <matrix-ui/CanvasHolder.h>

using rgb_matrix::Canvas;
using namespace std;

class Dot : public Component {
public:
    static const Color DEFAULT_DOT_COLOR;
    static const Layout DEFAULT_DOT_LAYOUT;

    Dot(string id, int x, int y);
    Dot(string id, int x, int y, int x_offset, int y_offset);

    virtual ~Dot();

    virtual int getWidth() const;

    virtual int getHeight() const;

    virtual void draw(Canvas &canvas);

private:
    int x;
    int y;
};

#endif /* DOT_H */

