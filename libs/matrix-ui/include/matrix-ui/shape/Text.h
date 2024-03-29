#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Layout.h>
#include <matrix-ui/CanvasHolder.h>

using rgb_matrix::Canvas;

class Text : public Component {
public:
    static const Color DEFAULT_TEXT_COLOR;
    static const Layout DEFAULT_TEXT_LAYOUT;

    Text(const string& id, const string& text, const rgb_matrix::Font *font, const Layout &layout = DEFAULT_TEXT_LAYOUT,
         int x_offset = 0,
         int y_offset = 0);

    virtual ~Text();

    void setText(string text);

    virtual int getWidth() const;

    virtual int getHeight() const;

    virtual void draw(Canvas &canvas);

private:
    string text;
    const rgb_matrix::Font *font;
};

#endif /* TEXT_H */

