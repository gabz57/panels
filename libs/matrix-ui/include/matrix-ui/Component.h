#ifndef COMPONENT_H
#define COMPONENT_H

#include <canvas.h>
#include <Layout.h>
#include <string>

using namespace rgb_matrix;

class Component {
public:
    Component(std::string id, int x_offset, int y_offset, Layout &layout);

    virtual ~Component();

    bool operator==(const Component &other);

    virtual void draw(Canvas &canvas, const Component *parent) const = 0;

    virtual int getWidth() const = 0;

    virtual int getHeight() const = 0;

    std::string getId() const;

    int xOffset() const;

    int yOffset() const;

    Layout &getLayout() const;


private:
    std::string id;
    int x_offset;
    int y_offset;
    Layout &layout;
};

#endif /* COMPONENT_H */

