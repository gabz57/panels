//
// Created by arnaud.schwartz on 2019-08-25.
//

#ifndef PANELS_PANELS_H
#define PANELS_PANELS_H

#include <string>
#include <memory>
#include <iostream>
#include <cstdio>

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

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf( new char[ size ] );
    snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}
#endif //PANELS_PANELS_H
