#ifndef TEXT_H
#define TEXT_H

#include <Component.h>
#include <string>
#include <graphics.h>
#include <Layout.h>
#include <canvas.h>

using rgb_matrix::Canvas;

class Text : public Component {
public:
    Text(std::string id, Layout &layout, std::string text, rgb_matrix::Font &font);

    Text(std::string id, Layout &layout, std::string text, rgb_matrix::Font &font, int x_offset, int y_offset);

    virtual ~Text();

    virtual int getWidth() const;

    virtual int getHeight() const;

    virtual void draw(Canvas &canvas) const;

private:
    std::string text;
    rgb_matrix::Font &font;
};

#endif /* TEXT_H */

