#ifndef PANELS_VERTICALSTRETCHINGTRANSFORMER_H
#define PANELS_VERTICALSTRETCHINGTRANSFORMER_H

#include <matrix-ui/animation/transformer/PixelTransformer.h>
#include <math.h>

class VerticalStretchingTransformer : public PixelTransformer {
public:
    VerticalStretchingTransformer(float factor, int axis_y, int resolution) :
            factor(factor),
            axis_y(axis_y),
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
        *new_x = x;
        *new_y = y + (int) ((progressFactor * (factor - 1)) * (float) (y - axis_y));
    }

    const float factor;
    const int axis_y;

    const int resolution;
    int progress;
};

#endif //PANELS_VERTICALSTRETCHINGTRANSFORMER_H
