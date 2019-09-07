#ifndef PANELS_CANVASHOLDER_H
#define PANELS_CANVASHOLDER_H

#include <canvas.h>
#include <led-matrix.h>
#include <matrix-ui/Component.h>

using namespace rgb_matrix;

class CanvasHolder {
public:
    CanvasHolder(rgb_matrix::RGBMatrix *matrix) : matrix(matrix) {
            offscreen = matrix->CreateFrameCanvas();
    }
    virtual ~CanvasHolder() {}

    FrameCanvas *getCanvas() {
        return offscreen;
    }

    void clear() {
        offscreen->Clear();
    }

    void renderAndSwap() {
        offscreen = matrix->SwapOnVSync(offscreen);
    }

private:
    RGBMatrix *matrix;
    FrameCanvas *offscreen;
};

#endif //PANELS_CANVASHOLDER_H
