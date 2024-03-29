#ifndef PANELS_TRANSLATIONTRANSFORMER_H
#define PANELS_TRANSLATIONTRANSFORMER_H

#include <matrix-ui/animation/transformer/PixelTransformer.h>
#include <iostream>
#include <math.h>

using namespace rgb_matrix;
using namespace std;

class TranslationTransformer : public PixelTransformer {
public:
    TranslationTransformer(int x = 0, int y = 0) :
            x_transl(x),
            y_transl(y),
            progress(0),
            max(std::max(std::abs(x), std::abs(y))) {}

    virtual ~TranslationTransformer() {
    }

    void Step() {
        if (progress < max) {
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
        Translate(x, y, matrix_x, matrix_y);
    }

private:
    void Translate(int x, int y, int *new_x, int *new_y) {
        float coef = max != 0 ? (float) progress / (float) max : 0;
        *new_x = (int) ((float) x + coef * (float) x_transl);
        *new_y = (int) ((float) y + coef * (float) y_transl);
    }

    const int x_transl;
    const int y_transl;
    int progress;
    const int max;
};

#endif //PANELS_TRANSLATIONTRANSFORMER_H
