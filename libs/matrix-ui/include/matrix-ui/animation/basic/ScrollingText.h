#ifndef PANELS_SCROLLINGTEXT_H
#define PANELS_SCROLLINGTEXT_H

#include <string>
#include <canvas.h>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/animation/AnimatedComponent.h>
#include <matrix-ui/Layout.h>
#include <matrix-ui/Text.h>
#include <matrix-ui/CanvasHolder.h>

static Layout DEFAULT_SCROLLING_TEXT_LAYOUT = Layout(Layout::FLOAT_LEFT);

class ScrollingText : public AnimatedComponent {
public:
    ScrollingText(std::string id, RGBMatrix *matrix,
                  std::string text, const rgb_matrix::Font *font,
                  int x_offset = 0, int y_offset = 0,
                  const Layout &layout = DEFAULT_SCROLLING_TEXT_LAYOUT);

    virtual ~ScrollingText();

    virtual int getWidth() const;

    virtual int getHeight() const;

    void drawNextFrame(CanvasHolder &canvasHandler, uint32_t *delay_us);

private:
    Text text;
};


#endif //PANELS_SCROLLINGTEXT_H
