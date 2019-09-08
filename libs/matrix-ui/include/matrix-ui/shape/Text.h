#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Layout.h>
#include <matrix-ui/CanvasHolder.h>

static Layout DEFAULT_TEXT_LAYOUT = Layout(Layout::FLOAT_LEFT);

using rgb_matrix::Canvas;

class Text : public Component {
public:
    Text(std::string id, std::string text, const rgb_matrix::Font *font, const Layout &layout = DEFAULT_TEXT_LAYOUT);

    Text(std::string id, std::string text, const rgb_matrix::Font *font, const Layout &layout = DEFAULT_TEXT_LAYOUT,
         int x_offset = 0,
         int y_offset = 0);

    virtual ~Text();

    virtual int getWidth() const;

    virtual int getHeight() const;

    virtual void draw(Canvas &canvas);

private:
    std::string text;
    const rgb_matrix::Font *font;
};

#endif /* TEXT_H */

