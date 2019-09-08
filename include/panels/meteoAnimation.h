#ifndef PANELS_METEOANIMATION_H
#define PANELS_METEOANIMATION_H

#include <iostream>
#include <led-matrix.h>
#include <panels/demoAnimation.h>
#include <matrix-ui/Panel.h>
#include <matrix-ui/RootPanel.h>
#include <matrix-ui/shape/Text.h>
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


Panel *buildMeteoPanel(const Font *font, int PANEL_WIDTH, int PANEL_HEIGHT, int LINE_HEIGHT, int LINE_WIDTH) {
    const MeteoData meteoData = retrieveMeteoData();
    Panel *meteoPanel = new Panel("meteoPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);

    meteoPanel->addComponent(new TextLine("cityLine", meteoData.city, "",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 0));
    meteoPanel->addComponent(new TemperatureLine("cityTemperature", "Température :",
                                                 meteoData.cityTemperature,
                                                 font, LINE_WIDTH, LINE_HEIGHT, 0, LINE_HEIGHT));

    meteoPanel->addComponent(new TemperatureLine("minTemperature", "Min :",
                                                 meteoData.minTemperature,
                                                 font, LINE_WIDTH, LINE_HEIGHT, 0, 2 * LINE_HEIGHT));
    meteoPanel->addComponent(new TemperatureLine("maxTemperature", "Max :",
                                                 meteoData.maxTemperature,
                                                 font, LINE_WIDTH, LINE_HEIGHT, 0, 3 * LINE_HEIGHT));
    meteoPanel->addComponent(new TextLine("humidity", "Humidité :", to_string(meteoData.humidity) + "%",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 4 * LINE_HEIGHT));
    return meteoPanel;
}

Panel *buildSensorPanel(const Font *font, int PANEL_WIDTH, int PANEL_HEIGHT, int LINE_HEIGHT, int LINE_WIDTH) {

    const GroundHumiditySensorData groundHumiditySensorData = retrieveGroundHumiditySensorData();
    const TemperatureSensorData temperatureSensorData = retrieveTemperatureSensorData();

    Panel *mainPanel = new Panel("sensorPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);

    //// BLOC HUMIDITÉ
    cout << "Drawing Sensors assembling panel humidity" << endl;
    Panel *upperPanel = new Panel("groundHumiditySensor", PANEL_WIDTH, PANEL_HEIGHT / 2, 0, 0);

    upperPanel->addComponent(new TextLine("titleLine", "Capteurs :", "",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 0));
    upperPanel->addComponent(new TextLine("lineOfEquals", "----------", "",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, LINE_HEIGHT));
    upperPanel->addComponent(new TextLine("groundHumiditySensor", "Humidité plante :", "",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 3 * LINE_HEIGHT));
    upperPanel->addComponent(new TextLine("groundHumiditySensorName", groundHumiditySensorData.name, "",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 4 * LINE_HEIGHT));
    upperPanel->addComponent(
            new TextLine("groundHumidityLine", "Humidité :", to_string(groundHumiditySensorData.humidity) + ".",
                         font, LINE_WIDTH, LINE_HEIGHT, 0, 5 * LINE_HEIGHT));
    upperPanel->addComponent(new TextLine("groundDryLine", "Sécheresse :", groundHumiditySensorData.dry ? "OUI" : "NON",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 6 * LINE_HEIGHT));

    mainPanel->addComponent(upperPanel);

    //// BLOC TEMPERATURE
    cout << "Drawing Sensors assembling panel temperature" << endl;
    Panel *lowerPanel = new Panel("temperatureSensor", PANEL_WIDTH, PANEL_HEIGHT / 2, 0, PANEL_HEIGHT / 2);

    lowerPanel->addComponent(new TextLine("temperatureSensorName", "Température pièce :", "",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 0));
    lowerPanel->addComponent(new TextLine("lineOfEquals2", "-------------------", "",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, LINE_HEIGHT));
    lowerPanel->addComponent(new TextLine("temperatureSensorName", temperatureSensorData.name, "",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 3 * LINE_HEIGHT));
    lowerPanel->addComponent(new TemperatureLine("temperature", "Température :",
                                                 temperatureSensorData.temperatureCelcius,
                                                 font, LINE_WIDTH, LINE_HEIGHT, 0, 5 * LINE_HEIGHT));
    lowerPanel->addComponent(new TemperatureLine("heatIndex", "Indice de chaleur :",
                                                 temperatureSensorData.heatIndexCelcius,
                                                 font, LINE_WIDTH, LINE_HEIGHT, 0, 6 * LINE_HEIGHT));
    lowerPanel->addComponent(new TextLine("humidity", "Humidité :",
                                          to_string(temperatureSensorData.humidity) + "%",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 7 * LINE_HEIGHT));

    mainPanel->addComponent(lowerPanel);
    return mainPanel;
}


#endif //PANELS_METEOANIMATION_H
