#ifndef LINE_H
#define LINE_H

#include <string>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Layout.h>
#include <matrix-ui/CanvasHolder.h>

using rgb_matrix::Canvas;

class Line : public Component {
public:
    static const Color DEFAULT_LINE_COLOR;
    static const Layout DEFAULT_LINE_LAYOUT;

    Line(string id, int x_start, int y_start, int x_end, int y_end);
    Line(string id, int x_start, int y_start, int x_end, int y_end, int x_offset, int y_offset);

    virtual ~Line();

    virtual int getWidth() const;

    virtual int getHeight() const;

    virtual void draw(Canvas &canvas);

private:
    int x_start;
    int y_start;
    int x_end;
    int y_end;
};

#endif /* LINE_H */

