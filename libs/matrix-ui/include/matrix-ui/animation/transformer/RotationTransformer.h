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
            progress(angleDec) {}

    virtual ~RotationTransformer() {
    }

    int getProgressAngle() {
        return progress;
    }

    void Step() {
        if (progress <= angle_) {
            progress++;
            NotifyObservers();
        }
    }

    void Reset() {
        progress = 0;
        NotifyObservers();
    }

    virtual void MapPixel(int x, int y, int *matrix_x, int *matrix_y) {
        Rotate(x, y, DegToRad((float) (progress % 360)), matrix_x, matrix_y);
    }

private:
    const float Pi = 3.141592653589793238463f;

    inline float DegToRad(float x) {
        return x / 180 * Pi;
    }

    void Rotate(int x, int y, float angle_rad, int *new_x, int *new_y) {
        *new_x = (int) (((float) (x - cent_x)) * cosf(angle_rad) - (float) (y - cent_y) * sinf(angle_rad) +
                        (float) cent_x);
        *new_y = (int) (((float) (x - cent_x)) * sinf(angle_rad) + (float) (y - cent_y) * cosf(angle_rad) +
                        (float) cent_y);
    }

    const int cent_x;
    const int cent_y;
    const int angle_;
    int progress;
};

#endif //PANELS_ROTATIONTRANSFORMER_H
