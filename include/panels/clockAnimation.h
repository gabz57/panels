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


Panel *buildClockAnimationPanel(int panelWidth, int panelHeight) {
    Panel *animationPanel = new Panel("animationPanel", panelWidth, panelHeight, 0, 0);

    Circle *circle = new Circle("circle", 64, 64, 58);

    Rectangle *rectangle2 = new Rectangle("rect", -1,9, 2,3,64,0);
    Line *line = new Line("dash", 52,-1, 55,-1,64,64);
    Line *line2 = new Line("dash2", 52,0, 55,0,64,64);
    animationPanel->addComponent(line);
    animationPanel->addComponent(line2);
    animationPanel->addComponent(rectangle2);
    animationPanel->addComponent(circle);

    return animationPanel;
}


#endif //PANELS_CLOCKANIMATION_H
