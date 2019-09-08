#ifndef PANELS_HORIZONTALSTRETCHINGTRANSFORMER_H
#define PANELS_HORIZONTALSTRETCHINGTRANSFORMER_H

#include <matrix-ui/animation/transformer/PixelTransformer.h>
#include <math.h>

class HorizontalStretchingTransformer : public PixelTransformer {
public:
    HorizontalStretchingTransformer(float factor, int axis_x, int resolution) :
            factor(factor),
            axis_x(axis_x),
            progress(0),
            resolution(resolution) {}

    void Step() {
        if (progress <= resolution) {
            progress++;
        }
    }

    void Reset() {
        progress = 0;
    }

    virtual void MapPixel(int x, int y, int *matrix_x, int *matrix_y) {
        Stretch(x, y, progressFactor(), matrix_x, matrix_y);
    }

private:

    inline float progressFactor() {
        return (float) progress / (float) resolution;
    }

    void Stretch(int x, int y, float progressFactor, int *new_x, int *new_y) {
        *new_x = x + (int) ((progressFactor * (factor - 1)) * (float) (x - axis_x));
        *new_y = y;
    }

    const int axis_x;
    const float factor;

    const int resolution;
    int progress;
};

#endif //PANELS_HORIZONTALSTRETCHINGTRANSFORMER_H
