#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <canvas.h>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Layout.h>

using rgb_matrix::Canvas;

class Text : public Component {
public:
    Text(std::string id, const Layout &layout, std::string text, const rgb_matrix::Font *font);

    Text(std::string id, const Layout &layout, std::string text, const rgb_matrix::Font *font, int x_offset, int y_offset);

    virtual ~Text();

    virtual int getWidth() const;

    virtual int getHeight() const;

    virtual void draw(Canvas &canvas) const;

private:
    std::string text;
    const rgb_matrix::Font *font;
};

#endif /* TEXT_H */

