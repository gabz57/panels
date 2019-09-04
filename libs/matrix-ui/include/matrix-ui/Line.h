#ifndef LINE_H
#define LINE_H

#include <string>
#include <canvas.h>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Layout.h>

using rgb_matrix::Canvas;

class Line : public Component {
public:
    Line(std::string id, int x_start, int y_start, int x_end, int y_end);
    Line(std::string id, int x_start, int y_start, int x_end, int y_end, int x_offset, int y_offset);

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

