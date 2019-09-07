#include "matrix-ui/animation/AnimatedComponent.h"
#include "matrix-ui/Component.h"
#include "led-matrix.h"
#include "matrix-ui/animation/CanvasAdapter.h"

AnimatedComponent::AnimatedComponent(std::string id, RGBMatrix *matrix,
                                     int x_offset, int y_offset, const Layout &layout) :
        Component(id, x_offset, y_offset, layout),
        ThreadedCanvasManipulator(matrix) {
}

AnimatedComponent::AnimatedComponent(std::string id, RGBMatrix *matrix,
                                     PixelTransformer *transformer,
                                     int x_offset, int y_offset, const Layout &layout) :
        Component(id, x_offset, y_offset, layout),
        ThreadedCanvasManipulator(matrix) {
    this->transformers.push_back(transformer);
}

AnimatedComponent::AnimatedComponent(std::string id, RGBMatrix *matrix,
                                     std::list<PixelTransformer *> &transformers,
                                     int x_offset, int y_offset, const Layout &layout) :
        Component(id, x_offset, y_offset, layout),
        ThreadedCanvasManipulator(matrix) {
    this->transformers.assign(transformers.begin(), transformers.end());
}

AnimatedComponent::~AnimatedComponent() {
    while (!transformers.empty()) {
        delete transformers.front(), transformers.pop_front();
    }
}

void AnimatedComponent::draw(CanvasHolder &canvasHandler) {
    this->canvasHandler = &canvasHandler;
    this->Start();
}

void AnimatedComponent::Run() {
    tmillis_t start_wait_ms = GetTimeInMillis();

    // TODO: extract duration
    tmillis_t duration_ms = 10000;
    tmillis_t end_time_ms = GetTimeInMillis() + duration_ms;
    uint32_t delay_us = 0;
    tmillis_t anim_delay_ms;
    tmillis_t time_already_spent;

    CanvasAdapter transformCanvas = CanvasAdapter(this, canvasHandler->getCanvas(), transformers);

    anim_delay_ms = render(delay_us, transformCanvas);

    time_already_spent = GetTimeInMillis() - start_wait_ms;
    SleepMillis(anim_delay_ms - time_already_spent);

    while (running() && /*!interrupt_received && */ GetTimeInMillis() <= end_time_ms) {
        start_wait_ms = GetTimeInMillis();
        transformCanvas.Clear();
        anim_delay_ms = render(delay_us, transformCanvas);

        // advance this component tranformers to build the next canvas
        for (PixelTransformer *transformer : transformers) {
            transformer->Step();
        }
        time_already_spent = GetTimeInMillis() - start_wait_ms;

        SleepMillis(anim_delay_ms - time_already_spent);
        // usleep(15 * 1000);
    }
}

tmillis_t AnimatedComponent::render(uint32_t &delay_us, Canvas &canvasTransformer) {
    tmillis_t anim_delay_ms;
    this->drawNextFrame(canvasTransformer, &delay_us);
    anim_delay_ms = delay_us / 1000;
    // FIXME:
    canvasHandler->renderAndSwap();
    return anim_delay_ms;
}

//virtual void drawNextFrame(CanvasHolder &canvasHandler, uint32_t *delay_us) = 0;
