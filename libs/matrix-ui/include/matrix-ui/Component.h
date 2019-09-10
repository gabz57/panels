#ifndef COMPONENT_H
#define COMPONENT_H

#include <matrix-ui/Layout.h>
#include <matrix-ui/CanvasHolder.h>
#include <matrix-ui/animation/CanvasAdapter.h>
#include <string>

using namespace std;
using namespace rgb_matrix;

class Component {
public:
    Component(const string &id, int x_offset, int y_offset, const Layout &layout);

    virtual ~Component();

    bool operator==(const Component &other);

    virtual int getWidth() const = 0;

    virtual int getHeight() const = 0;

    const Component *getParent() const;

    void setParent(const Component *parent);

    string getId() const;

    int xOffset() const;

    int yOffset() const;

    Layout &getLayout();

    Canvas *canvasAdapter(Canvas &canvas);

    void drawComponent(Canvas &canvas) {
        Canvas* adapter = new CanvasAdapter(&canvas, layout.getTransformers());
        this->draw(*adapter);
        delete adapter;
    }

protected:

    int x_offset;
    int y_offset;
    Layout layout;
private:
    virtual void draw(Canvas &canvas) = 0;

    string id;
    const Component *parent = nullptr;
};

#endif /* COMPONENT_H */

