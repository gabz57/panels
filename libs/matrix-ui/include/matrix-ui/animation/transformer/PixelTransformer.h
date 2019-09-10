#ifndef PANELS_PIXELTRANSFORMER_H
#define PANELS_PIXELTRANSFORMER_H

#include <matrix-ui/dp/Observee.h>
#include <stdint.h>

class PixelTransformer : public Observee {
public:
    virtual ~PixelTransformer() {}

    virtual void MapPixel(int x, int y, int *matrix_x, int *matrix_y, int red, int green, int blue,
                          int *r_mod, int *g_mod, int *b_mod) = 0;

    virtual void Step() = 0;

    virtual void Reset() = 0;
};

#endif //PANELS_PIXELTRANSFORMER_H
