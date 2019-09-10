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
#include <matrix-ui/animation/transformer/ColorTransformer.h>
#include <matrix-ui/animation/transformer/RotationTransformer.h>
#include <matrix-ui/animation/AnimationComponent.h>
#include <matrix-ui/dp/Observer.h>
#include <matrix-ui/dp/Observee.h>

#include <unistd.h>
#include <cstdio>
#include <csignal>

const Color *circleColor = new Color(255, 0, 0);
const Color *secondCursorColor = new Color(255, 255, 255);
const Color *textColor = new Color(255, 255, 255);
static bool alternativeColor = true;

class AngleObserver : public Observer {
public:
    AngleObserver(list<Component *> *dots, Panel *dateTimePanel) : dots(dots), dateTimePanel(dateTimePanel) {

    }

    ~AngleObserver() override = default;

    void Notify(Observee *observee) override {
        auto *rotationTransformer = dynamic_cast<RotationTransformer *>(observee);
        if (rotationTransformer != nullptr) {
            int angle = rotationTransformer->getProgressAngle();
            if (!dots->empty() && angle % 6 == 0) {
                int index = angle / 6;
                if (index < dots->size()) {
                    auto it = std::next(dots->begin(), index);
                    Component *component = *it;
                    component->getLayout().setColor(alternativeColor ? *secondCursorColor : *circleColor);
                }
            }
            if (angle == 0) {
                alternativeColor = !alternativeColor;
            }
        }

        time_t curr_time;
        time(&curr_time);
        tm *curr_tm = localtime(&curr_time);

        char date_string[100];
        char time_string[100];
        strftime(date_string, 50, "%d-%m-%Y", curr_tm);
        strftime(time_string, 50, "%T", curr_tm);

//        cout << date_string << endl;
//        cout << time_string << endl;

        Text *datePanel = dynamic_cast<Text *>(dateTimePanel->getComponents()->find("date")->second);
        Text *timePanel = dynamic_cast<Text *>(dateTimePanel->getComponents()->find("time")->second);
        datePanel->setText(date_string);
        timePanel->setText(time_string);
    };

private:
    Panel *dateTimePanel;
    list<Component *> *dots;
};

Panel *buildClockAnimationPanel(int panelWidth, int panelHeight) {
    auto *animationPanel = new Panel("animationPanel", panelWidth, panelHeight, 0, 0);
    // Hours
    auto *rectangleTemplate = new Rectangle("rect", 0, 9, 1, 5, 63, 0);
    for (int i = 0; i < 12; i++) {
        auto *rotationTransformer = new RotationTransformer(i * 360 / 12, 64, 64);
        auto adaptedLayout = new Layout(rectangleTemplate->getLayout(), rotationTransformer);
        auto *newRectangle = new Rectangle(rectangleTemplate, "rect#" + to_string(i), *adaptedLayout);
        animationPanel->addComponent(newRectangle);
    }

    // Seconds
    auto *dots = new list<Component *>();
    auto *dotTemplate = new Dot("dot", 0, 9, 63, 0);
    for (int i = 0; i < 60; i++) {
        auto *rotationTransformer = new RotationTransformer(i * 360 / 60, 64, 64);
        auto adaptedLayout = new Layout(dotTemplate->getLayout(), rotationTransformer);
        Dot *newDot = new Dot(dotTemplate, "dot#" + to_string(i), *adaptedLayout);
        animationPanel->addComponent(newDot);
        dots->push_back(newDot);
    }

    // Circle
    auto colorTransformer = new ColorTransformer(0, 0, 128, 128);
    auto circleLayout = new Layout(Floating::FLOAT_LEFT, *circleColor, colorTransformer);
    auto *circle = new Circle("circle", 64, 64, 58, 0, 0, *circleLayout);
    animationPanel->addComponent(circle);

    // Rotating cursor - moving second
    time_t curr_time;
    time(&curr_time);
    tm *curr_tm = localtime(&curr_time);
    auto *rectangleSeconds = new Rectangle("secondsRect", 0, 9, 1, 1, 63, 0,
                                           Layout(Floating::FLOAT_LEFT, *secondCursorColor));
    auto *rotationTransformer = new RotationTransformer(360, 64, 64, curr_tm->tm_sec * 6);
    list<PixelTransformer *> transformers;
    transformers.push_back(rotationTransformer);
    transformers.push_back(colorTransformer);
    Observee *observableRotationTransformer = rotationTransformer;
    auto *parentAnimComponent = new AnimationComponent(rectangleSeconds, &transformers, 360, 60000, true,
                                                       curr_tm->tm_sec * 1000000);
    animationPanel->addComponent(parentAnimComponent);

    // populate map somehow

    // TIME TEXT

    // FIXME Font memory leaks
    const char *bdf_font_file = "/home/pi/Desktop/leds/rpi-rgb-led-matrix/fonts/5x7.bdf";
    auto *font = new Font();
    if (!font->LoadFont(bdf_font_file)) {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
    }
    int lineHeight = font->height() + 1;
//    int lineWidth = panelWidth;

    auto *dateTimePanel = new Panel("dateTimePanel", 160, panelHeight, 38, 64);
//    auto colorTransformer = new ColorTransformer(0,0,128,128);
//    auto adaptedPanelLayout = new Layout(Floating ::FLOAT_LEFT, *circleColor, colorTransformer);

    Text *time = new Text("time", "", font, *new Layout(Floating::FLOAT_LEFT, *textColor, colorTransformer), 6, -(lineHeight + 2));
    Text *date = new Text("date", "", font, *new Layout(Floating::FLOAT_LEFT, *textColor, colorTransformer), 1, 2);
    dateTimePanel->addComponent(time);
    dateTimePanel->addComponent(date);

    animationPanel->addComponent(dateTimePanel);

    // color switch for seconds
    Observer *angleObserver = new AngleObserver(dots, dateTimePanel);
    observableRotationTransformer->AddObserver(angleObserver);

    return animationPanel;
}


#endif //PANELS_CLOCKANIMATION_H
