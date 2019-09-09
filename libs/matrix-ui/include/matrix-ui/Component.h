#ifndef COMPONENT_H
#define COMPONENT_H

#include <matrix-ui/Layout.h>
#include <matrix-ui/CanvasHolder.h>
#include <string>

using namespace std;
using namespace rgb_matrix;

class Component {
public:
    Component(string id, int x_offset, int y_offset, const Layout &layout);

    virtual ~Component();

    bool operator==(const Component &other);

    virtual void draw(CanvasHolder &canvasHandler) {
        draw(*canvasHandler.getCanvas());
    }

    virtual void draw(Canvas &canvas) = 0;

    virtual int getWidth() const = 0;

    virtual int getHeight() const = 0;

    const Component *getParent() const;

    void setParent(const Component *parent);

    string getId() const;

    int xOffset() const;

    int yOffset() const;

    const Layout &getLayout() const;

    Canvas * getPreCanvas(Canvas &canvas);

private:
    string id;
    const Component *parent = nullptr;
protected:
    int x_offset;
    int y_offset;
    const Layout layout;
};

#endif /* COMPONENT_H */

