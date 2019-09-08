#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Layout.h>
#include <matrix-ui/CanvasHolder.h>

using rgb_matrix::Canvas;

class Circle : public Component {
public:
    static const Color DEFAULT_CIRCLE_COLOR;
    static const Layout DEFAULT_CIRCLE_LAYOUT;

    Circle(string id, int x_center, int y_center, int radius, int x_offset = 0, int y_offset = 0, const Layout &layout = DEFAULT_CIRCLE_LAYOUT);

    virtual ~Circle();

    virtual int getWidth() const;

    virtual int getHeight() const;

    virtual void draw(Canvas &canvas);

private:
  int x_center;
  int y_center;
  int radius;
};

#endif /* CIRCLE_H */

