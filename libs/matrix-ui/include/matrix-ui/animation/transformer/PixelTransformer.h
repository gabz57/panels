#ifndef PANELS_PIXELTRANSFORMER_H
#define PANELS_PIXELTRANSFORMER_H

class PixelTransformer {
public:
    virtual ~PixelTransformer() {}

    virtual void MapPixel(int x, int y, int *matrix_x, int *matrix_y) = 0;

    virtual void Step() = 0;

    virtual void Reset() = 0;
};

#endif //PANELS_PIXELTRANSFORMER_H
