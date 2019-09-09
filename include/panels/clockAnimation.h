#ifndef PANELS_CLOCKANIMATION_H
#define PANELS_CLOCKANIMATION_H

#include <iostream>
#include <led-matrix.h>
#include <panels/demoAnimation.h>
#include <matrix-ui/Panel.h>
#include <matrix-ui/RootPanel.h>
#include <matrix-ui/shape/Text.h>
#include <matrix-ui/shape/Line.h>
#include <matrix-ui/shape/Dot.h>
#include <matrix-ui/shape/Rectangle.h>
#include <matrix-ui/shape/Circle.h>
#include <matrix-ui/TemperatureLine.h>
#include <matrix-ui/shape/TextLine.h>
#include <matrix-ui/CanvasHolder.h>
#include <matrix-ui/animation/transformer/TranslationTransformer.h>
#include <matrix-ui/animation/transformer/VerticalStretchingTransformer.h>
#include <matrix-ui/animation/transformer/RotationTransformer.h>
#include <matrix-ui/animation/AnimationComponent.h>

#include <unistd.h>
#include <cstdio>
#include <csignal>

const Color *circleColor = new Color(255,0,0);
const Color *secondCursorColor = new Color(255,255,255);

Panel *buildClockAnimationPanel(int panelWidth, int panelHeight) {
    Panel *animationPanel = new Panel("animationPanel", panelWidth, panelHeight, 0, 0);

    Circle *circle = new Circle("circle", 64, 64, 58, 0, 0, Layout(Floating::FLOAT_LEFT, *circleColor));

    Rectangle *rectangleTemplate = new Rectangle("rect", 0, 9, 1, 10, 63, 0);
    for (int i = 0; i < 12; i++) {
        std::list<PixelTransformer *> transformers = std::list<PixelTransformer *>();
        RotationTransformer *rotationTransformer = new RotationTransformer(i * 360 / 12, 64, 64);
        transformers.push_back(rotationTransformer);
        Layout* adaptedLayout = new Layout(rectangleTemplate->getLayout(), transformers);
        Rectangle* newRectangle = new Rectangle(rectangleTemplate, "rect#" + to_string(i), *adaptedLayout);
        animationPanel->addComponent(newRectangle);
    }
    Dot *dotTemplate = new Dot("dot", 0, 9, 63, 0);

    for (int i = 0; i < 60; i++) {
        std::list<PixelTransformer *> transformers = std::list<PixelTransformer *>();
        RotationTransformer *rotationTransformer = new RotationTransformer(i * 360 / 60, 64, 64);
        transformers.push_back(rotationTransformer);
        Layout* adaptedLayout = new Layout(dotTemplate->getLayout(), transformers);
        Dot* newDot = new Dot(dotTemplate, "dot#" + to_string(i), *adaptedLayout);
        animationPanel->addComponent(newDot);
    }
////    this->layout.setTransformers(transformers);
//
//    Line *line = new Line("dash", 52, -1, 55, -1, 64, 64);
//    Line *line2 = new Line("dash2", 52, 0, 55, 0, 64, 64);
//    animationPanel->addComponent(line);
//    animationPanel->addComponent(line2);
////    animationPanel->addComponent(rectangle);
    animationPanel->addComponent(circle);

    Rectangle *rectangleSeconds = new Rectangle("secondsRect", 0, 9, 1, 1, 63, 0, Layout(Floating::FLOAT_LEFT, *secondCursorColor));
    RotationTransformer *rotationTransformer = new RotationTransformer(720, 64, 64);
    AnimationComponent *parentAnimComponent = new AnimationComponent(rectangleSeconds, rotationTransformer, 720, 30000, true);
    animationPanel->addComponent(parentAnimComponent);

    return animationPanel;
}


#endif //PANELS_CLOCKANIMATION_H
