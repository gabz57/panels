#ifndef PANELS_ROTATIONTRANSFORMER_H
#define PANELS_ROTATIONTRANSFORMER_H

#include <matrix-ui/animation/transformer/PixelTransformer.h>
#include <math.h>

class RotationTransformer : public PixelTransformer {
public:
    RotationTransformer(int angleDec, int cent_x, int cent_y) :
            angle_(angleDec),
            cent_x(cent_x),
            cent_y(cent_y),
            progress(0) {}

//    virtual bool GetSizeMapping(int matrix_width, int matrix_height,
//                                int *visible_width, int *visible_height)
//    const {
//        if (angle_ % 180 == 0) {
//            *visible_width = matrix_width;
//            *visible_height = matrix_height;
//        } else {
//            *visible_width = matrix_height;
//            *visible_height = matrix_width;
//        }
//        return true;
//    }

    void Step() {
        progress++;
        progress %= angle_;
    }

    virtual void MapPixel(int x, int y, int *matrix_x, int *matrix_y) {
        Rotate(x, y, angle_ != 0 ? (float) angle_ * (float) progress / (float) angle_ : 0, matrix_x, matrix_y);
    }

private:
    void Rotate(int x, int y, float angle, int *new_x, int *new_y) {
        *new_x = (int) (((float) (x - cent_x)) * cosf(angle) - (float) (y - cent_y) * sinf(angle) + (float) cent_x);
        *new_y = (int) (((float) (x - cent_x)) * sinf(angle) + (float) (y - cent_y) * cosf(angle) + (float) cent_y);
    }

    const int cent_x;
    const int cent_y;
    const int angle_;
    int progress;
};

#endif //PANELS_ROTATIONTRANSFORMER_H
