#ifndef PANELS_ANIMATIONENDLISTENER_H
#define PANELS_ANIMATIONENDLISTENER_H

class AnimationEndListener {
public:
    virtual void onEnd() const = 0;

    AnimationEndListener() = default;

    AnimationEndListener(const AnimationEndListener &) = delete;

    AnimationEndListener &operator=(const AnimationEndListener &) = delete;
};

#endif //PANELS_ANIMATIONENDLISTENER_H
