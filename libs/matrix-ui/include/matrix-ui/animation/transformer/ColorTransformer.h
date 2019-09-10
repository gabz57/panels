#ifndef PANELS_COLORTRANSFORMER_H
#define PANELS_COLORTRANSFORMER_H

#include <matrix-ui/animation/transformer/PixelTransformer.h>
#include <iostream>
#include <math.h>

using namespace rgb_matrix;
using namespace std;

class ColorTransformer : public PixelTransformer {
public:
    ColorTransformer(
            int x_start,
            int y_start,
            int width,
            int height
    ) : x_start(x_start),
        y_start(y_start),
        width(width),
        height(height) {}

    virtual ~ColorTransformer() {
    }

    void Step() {
    }

    void Reset() {
    }

    virtual void MapPixel(int x, int y, int *matrix_x, int *matrix_y,
                          int red, int green, int blue,
                          int *r_mod, int *g_mod, int *b_mod) {
        *r_mod = scale_col(x, x_start, x_start + width);
        *g_mod = 255 - scale_col(y, y_start, y_start + height);
        *b_mod = scale_col(y, y_start, y_start + height);
    }

private:
    static int scale_col(int val, int lo, int hi) {
        if (val < lo) return 0;
        if (val > hi) return 255;
        return 255 * (val - lo) / (hi - lo);
    }

    const int x_start;
    const int y_start;
    const int width;
    const int height;
};

#endif //PANELS_COLORTRANSFORMER_H
