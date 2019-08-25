#ifndef PANELS_PANELS_H
#define PANELS_PANELS_H

#include <string>

typedef struct meteoData {
    std::string city;
    int cityTemperature;
    int minTemperature;
    int maxTemperature;
    int humidity;

    meteoData(std::string city, int cityTemperature, int minTemperature, int maxTemperature, int humidity) :
            city(city),
            cityTemperature(cityTemperature),
            minTemperature(minTemperature),
            maxTemperature(maxTemperature),
            humidity(humidity) {
    }

} MeteoData;

typedef struct groundHumiditySensorData {
    std::string name;
    int humidity;
    bool dry;

    groundHumiditySensorData(std::string name, int humidity, bool dry) :
            name(name),
            humidity(humidity),
            dry(dry) {}
} GroundHumiditySensorData;

typedef struct temperatureSensorData {
    std::string name;
    int humidity;
    int temperatureCelcius;
    int heatIndexCelcius;

    temperatureSensorData(
            std::string name,
            int humidity,
            int temperatureCelcius,
            int heatIndexCelcius
    ) :
            name(name),
            humidity(humidity),
            temperatureCelcius(temperatureCelcius),
            heatIndexCelcius(heatIndexCelcius) {}
} TemperatureSensorData;

#endif //PANELS_PANELS_H
