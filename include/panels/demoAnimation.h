#ifndef PANELS_DEMOANIMATION_H
#define PANELS_DEMOANIMATION_H

#include <iostream>
#include <led-matrix.h>
#include <panels/demoAnimation.h>
#include <matrix-ui/Panel.h>
#include <matrix-ui/RootPanel.h>
#include <matrix-ui/shape/Text.h>
#include <matrix-ui/shape/Dot.h>
#include <matrix-ui/shape/Rectangle.h>
#include <matrix-ui/shape/Circle.h>
#include <matrix-ui/samples/TemperatureLine.h>
#include <matrix-ui/shape/TextLine.h>
#include <matrix-ui/CanvasHolder.h>
#include <matrix-ui/animation/transformer/base/TranslationTransformer.h>
#include <matrix-ui/animation/transformer/base/VerticalStretchingTransformer.h>
#include <matrix-ui/animation/transformer/base/RotationTransformer.h>
#include <matrix-ui/animation/AnimationComponent.h>

#include <unistd.h>
#include <cstdio>
#include <csignal>


Panel *buildDemoAnimationPanel(const Font *font, int PANEL_WIDTH, int PANEL_HEIGHT, int LINE_HEIGHT, int LINE_WIDTH) {
    Panel *animationPanel = new Panel("animationPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);

    Rectangle *rectangle = new Rectangle("rectangle", 64, 64, 20, 20, -10, -10);
    RotationTransformer *rotationTransformer4 = new RotationTransformer(360, 64, 64);
    AnimationComponent *animComponent5 = new AnimationComponent(rectangle, rotationTransformer4, 360, 2500, true);
    animationPanel->addComponent(animComponent5);

    Rectangle *rectangle2 = new Rectangle("rectangle2", 32, 96, 20, 20, -10, -10);
    VerticalStretchingTransformer *verticalStretchingTransformer = new VerticalStretchingTransformer(0.5, 86, 128);
    AnimationComponent *animComponent6 = new AnimationComponent(rectangle2, verticalStretchingTransformer, 128, 2500,
                                                                true);
    animationPanel->addComponent(animComponent6);

    Circle *circle = new Circle("circle", 96, 96, 20);
    VerticalStretchingTransformer *verticalStretchingTransformer2 = new VerticalStretchingTransformer(0.5, 86, 128);
    AnimationComponent *animComponent7 = new AnimationComponent(circle, verticalStretchingTransformer2, 128, 2500,
                                                                true);
    animationPanel->addComponent(animComponent7);

    TextLine *textLine = new TextLine("cityLine", "How are you ?", "Fine ?", font, LINE_WIDTH, LINE_HEIGHT, 0, 0);
    TranslationTransformer *translationTransformer = new TranslationTransformer(20, 20);
    AnimationComponent *animComponent = new AnimationComponent(textLine, translationTransformer, 20, 5000);
    animationPanel->addComponent(animComponent);

    TextLine *textLine2 = new TextLine("cityLine2", "Oh yeah !", "++", font, LINE_WIDTH, LINE_HEIGHT, 0, LINE_HEIGHT);
    TranslationTransformer *translationTransformer2 = new TranslationTransformer(0, 30);
    AnimationComponent *animComponent2 = new AnimationComponent(textLine2, translationTransformer2, 30, 2000);
    animationPanel->addComponent(animComponent2);

//    Text *text = new Text("wordLine", "Oh yeah !", font, DEFAULT_TEXT_LAYOUT, 64, 64);
//    std::list<PixelTransformer *> transformers =  std::list<PixelTransformer *>();
//    transformers.push_back(rotationTransformer);
//    transformers.push_back(translationTransformer3);
    Text *text = new Text("wordLine", "Oh yeah !", font, Text::DEFAULT_TEXT_LAYOUT, 16, 16);
    RotationTransformer *rotationTransformer = new RotationTransformer(360, 16, 16);
    AnimationComponent *subAnimComponent = new AnimationComponent(text, rotationTransformer, 360, 4000);

    TranslationTransformer *translationTransformer3 = new TranslationTransformer(32, 32);
    AnimationComponent *animComponent3 = new AnimationComponent(subAnimComponent, translationTransformer3, 32, 4000);
    RotationTransformer *rotationTransformer2 = new RotationTransformer(360, 64, 64);
    AnimationComponent *parentAnimComponent = new AnimationComponent(animComponent3, rotationTransformer2, 360, 2000);
    animationPanel->addComponent(parentAnimComponent);

    Dot *dot = new Dot("dot", 0, 0);
    Dot *dot2 = new Dot("dot2", 0, 32);
    Dot *dot3 = new Dot("dot3", 0, 46);
    Dot *dot4 = new Dot("dot4", 0, 54);

    Panel *panel = new Panel("secondsPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);
    panel->addComponent(dot);
    panel->addComponent(dot2);
    panel->addComponent(dot3);
    panel->addComponent(dot4);
    RotationTransformer *rotationTransformer3 = new RotationTransformer(4 * 360, 0, 64);
    AnimationComponent *animComponent4 = new AnimationComponent(panel, rotationTransformer3, 4 * 360, 4 * 60000);

    Panel *parentPanel = new Panel("parentPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);
    parentPanel->addComponent(animComponent4);

    animationPanel->addComponent(parentPanel);


    return animationPanel;
}


#endif //PANELS_DEMOANIMATION_H
