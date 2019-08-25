#ifndef PANEL_H
#define PANEL_H

#include <unordered_map>
#include <string>
#include <iterator>
#include <canvas.h>
#include <Component.h>
#include <Layout.h>
static Layout DEFAULT_LAYOUT = Layout(Layout::FLOAT_LEFT);

class Panel : public Component {
public:
    Panel(std::string id, int width, int height, int x_offset, int y_offset, Layout &layout = DEFAULT_LAYOUT);

    virtual ~Panel();

    virtual int getWidth() const; // Pixels available in x direction.
    virtual int getHeight() const; // Pixels available in y direction.

    void addComponent(Component* component);
    virtual void draw(Canvas& canvas, const Component* parent) const;
private:
    int width;
    int height;
    std::unordered_map<std::string, Component*> components;
};

#endif /* PANEL_H */

