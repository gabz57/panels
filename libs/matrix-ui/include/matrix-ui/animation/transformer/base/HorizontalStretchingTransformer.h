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

    virtual ~HorizontalStretchingTransformer() {
    }

    void Step() {
        if (progress <= resolution) {
            progress++;
            NotifyObservers();
        }
    }

    void Reset() {
        progress = 0;
        NotifyObservers();
    }

    virtual void MapPixel(int x, int y, int *matrix_x, int *matrix_y, int red, int green, int blue,
                          int *r_mod, int *g_mod, int *b_mod) {
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
