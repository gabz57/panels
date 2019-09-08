#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Layout.h>
#include <matrix-ui/CanvasHolder.h>

using rgb_matrix::Canvas;

class Rectangle : public Component {
public:
    static const Color DEFAULT_RECTANGLE_COLOR;
    static const Layout DEFAULT_RECTANGLE_LAYOUT;

    Rectangle(string id, int x, int y, int width, int height, int x_offset = 0, int y_offset = 0);

    virtual ~Rectangle();

    virtual int getWidth() const;

    virtual int getHeight() const;

    virtual void draw(Canvas &canvas);

private:
    int x;
    int y;
    int width;
    int height;
};

#endif /* RECTANGLE_H */

