#ifndef PANELS_CANVASADAPTER_H
#define PANELS_CANVASADAPTER_H

#include <canvas.h>
#include "led-matrix.h"
#include "graphics.h"
#include <list>
#include <matrix-ui/animation/transformer/PixelTransformer.h>

class CanvasAdapter : public rgb_matrix::Canvas {
public:
    CanvasAdapter(rgb_matrix::Canvas *canvas, std::list<PixelTransformer *> &transformers) : delegatee_(canvas) {
        this->transformers.assign(transformers.begin(), transformers.end());
    }

    virtual ~CanvasAdapter() {}

    int width() const { return delegatee_->width(); }

    int height() const { return delegatee_->height(); }

//    void SetBrightness(uint8_t b) { delegatee_->SetBrightness(b); }

    void SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
        int x_mod = x;
        int y_mod = y;
        for (PixelTransformer *pixelTransformer : transformers) {
            pixelTransformer->MapPixel(x_mod, y_mod, &x_mod, &y_mod);
        }

// <=> // if (x_mod >= min_display_x && x_mod < max_display_x && y_mod >= min_display_y && y_mod < max_display_y) {
//        if (x_mod >= 0 && x_mod < delegatee_->width()
//         && y_mod >= 0 && y_mod < delegatee_->height()) {
            delegatee_->SetPixel(x_mod, y_mod, red, green, blue);
//        }
    }

//    rgb_matrix::Color GetPixel(int x, int y);

    void Clear() {
        // FIXME: apply some mask to only turn off component view zone, here all matrix is cleared
        // component
        // transformers
        delegatee_->Clear();
    }

    // Fill screen with given 24bpp color.
    void Fill(uint8_t red, uint8_t green, uint8_t blue) {
        delegatee_->Fill(red, green, blue);
    }

    rgb_matrix::Canvas *getFrameCanvas() {
        return delegatee_;
    }

private:
    std::list<PixelTransformer *> transformers;
    rgb_matrix::Canvas *const delegatee_;
};

#endif //PANELS_CANVASADAPTER_H

//bool AnimatedComponent::ApplyPixelMapper(const PixelTransformer *mapper) {
//    if (mapper == NULL) return true;
////    using internal::PixelDesignatorMap;
//    const int old_width = this->width();
//    const int old_height = shared_pixel_mapper_->height();
//    int new_width, new_height;
//    if (!mapper->GetSizeMapping(old_width, old_height, &new_width, &new_height)) {
//        return false;
//    }
//    PixelDesignatorMap *new_mapper = new PixelDesignatorMap(
//            new_width, new_height, shared_pixel_mapper_->GetFillColorBits());
//    for (int y = 0; y < new_height; ++y) {
//        for (int x = 0; x < new_width; ++x) {
//            int orig_x = -1, orig_y = -1;
//            mapper->MapPixel(old_width, old_height, x, y, &orig_x, &orig_y);
//            if (orig_x < 0 || orig_y < 0 ||
//                orig_x >= old_width || orig_y >= old_height) {
//                fprintf(stderr, "Error in PixelMapper: (%d, %d) -> (%d, %d) [range: "
//                                "%dx%d]\n", x, y, orig_x, orig_y, old_width, old_height);
//                continue;
//            }
//            const internal::PixelDesignator *orig_designator;
//            orig_designator = shared_pixel_mapper_->get(orig_x, orig_y);
//            *new_mapper->get(x, y) = *orig_designator;
//        }
//    }
//    delete shared_pixel_mapper_;
//    shared_pixel_mapper_ = new_mapper;
//    return true;
//}