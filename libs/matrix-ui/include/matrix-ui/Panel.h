#ifndef PANEL_H
#define PANEL_H

#include <unordered_map>
#include <string>
#include <iterator>
#include <matrix-ui/Component.h>
#include <matrix-ui/CanvasHolder.h>
#include <matrix-ui/Layout.h>

static const Layout DEFAULT_LAYOUT = Layout(Layout::FLOAT_LEFT);

class Panel : public Component {
public:
    Panel(string id, int width, int height, int x_offset, int y_offset, const Layout &layout = DEFAULT_LAYOUT);

    virtual ~Panel();

    virtual int getWidth() const;

    virtual int getHeight() const;

    void addComponent(Component *component);

    virtual void draw(Canvas &canvas);

protected:
    std::unordered_map<std::string, Component *> components;
private:
    int width;
    int height;
};

#endif /* PANEL_H */

