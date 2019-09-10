#ifndef PANELS_ROOTPANEL_H
#define PANELS_ROOTPANEL_H

#include <string>
#include <canvas.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/CanvasHolder.h>

class RootPanel : public Component {
public:
    RootPanel(const string& id, int width, int height, CanvasHolder &canvasHandler, Component* childComponent);

    virtual ~RootPanel();

    void render();

    virtual void draw(Canvas &canvas);

    virtual int getWidth() const;

    virtual int getHeight() const;


private:
    int width;
    int height;
    CanvasHolder &canvasHandler;
    Component* childComponent;
};

#endif //PANELS_ROOTPANEL_H
