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
    TextLine(std::string id, std::string leftText, std::string rightText, const rgb_matrix::Font *font,
             int width, int height,
             int x_offset = 0, int y_offset = 0,
             Layout &layout = DEFAULT_LAYOUT,
             int xLeftOffset = 0, int yLeftOffset = 0,
             int xRightOffset = 0, int yRightOffset = 0);

    virtual ~TextLine();

};


#endif //PANELS_TEXTLINE_H
