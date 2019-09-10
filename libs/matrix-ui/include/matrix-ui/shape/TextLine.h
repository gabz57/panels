#ifndef PANELS_TEXTLINE_H
#define PANELS_TEXTLINE_H

#include <string>
#include <canvas.h>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Panel.h>
#include <matrix-ui/Layout.h>


class TextLine : public Panel {
public:
    static const Color DEFAULT_TEXTLINE_COLOR;
    static const Layout DEFAULT_TEXTLINE_LAYOUT;

    TextLine(const string &id, const string &leftText, const string &rightText, const rgb_matrix::Font *font,
             int width, int height,
             int x_offset = 0, int y_offset = 0,
             const Layout &layout = DEFAULT_TEXTLINE_LAYOUT,
             int xLeftOffset = 0, int yLeftOffset = 0,
             int xRightOffset = 0, int yRightOffset = 0);

    virtual ~TextLine();

};


#endif //PANELS_TEXTLINE_H
