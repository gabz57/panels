#ifndef ANIMATEDCOMPONENT_H
#define ANIMATEDCOMPONENT_H

#include <string>
#include <list>
#include <canvas.h>
#include <led-matrix.h>
#include <graphics.h>
#include <threaded-canvas-manipulator.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Layout.h>
#include <matrix-ui/CanvasHolder.h>
#include <matrix-ui/animation/LocalTime.h>
#include <matrix-ui/animation/CanvasAdapter.h>
#include <matrix-ui/animation/transformer/PixelTransformer.h>

static Layout DEFAULT_ANIMATED_LAYOUT = Layout(Layout::FLOAT_LEFT);

class AnimatedComponent : public Component, public ThreadedCanvasManipulator {
public:
    AnimatedComponent(std::string id, RGBMatrix *matrix,
                      int x_offset = 0, int y_offset = 0, const Layout &layout = DEFAULT_ANIMATED_LAYOUT);

    AnimatedComponent(std::string id, RGBMatrix *matrix,
                      PixelTransformer *transformer,
                      int x_offset = 0, int y_offset = 0, const Layout &layout = DEFAULT_ANIMATED_LAYOUT);

    AnimatedComponent(std::string id, RGBMatrix *matrix,
                      std::list<PixelTransformer *> &transformers,
                      int x_offset = 0, int y_offset = 0, const Layout &layout = DEFAULT_ANIMATED_LAYOUT);

    virtual ~AnimatedComponent();

    virtual int getWidth() const = 0;

    virtual int getHeight() const = 0;

    void Run();

    void draw(CanvasHolder &canvasHandler);

    virtual void drawNextFrame(Canvas &canvasHandler, uint32_t *delay_us) = 0;

protected:
    std::list<PixelTransformer *> transformers;

private:
    CanvasHolder* canvasHandler;

    tmillis_t render(uint32_t &delay_us, Canvas &canvasTransformer);
};


#endif //ANIMATEDCOMPONENT_H
