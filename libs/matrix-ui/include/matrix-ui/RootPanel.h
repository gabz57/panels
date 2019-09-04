#ifndef PANELS_ROOTPANEL_H
#define PANELS_ROOTPANEL_H

#include <string>
#include <canvas.h>
#include <matrix-ui/Component.h>

class RootPanel : public Component {
public:
    RootPanel(std::string id, int width, int height, Component* childComponent);

    virtual ~RootPanel();

    virtual void draw(Canvas &canvas);

    virtual int getWidth() const;

    virtual int getHeight() const;

private:
    int width;
    int height;
    Component* childComponent;
};

#endif //PANELS_ROOTPANEL_H
