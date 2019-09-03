#ifndef PANELS_PANELS_H
#define PANELS_PANELS_H

#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "influxdb.hpp"

using namespace std;

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

static GroundHumiditySensorData retrieveGroundHumiditySensorData() {
    influxdb_cpp::server_info serverInfo("127.0.0.1", 8086, "", "test", "test");
    string resp;
    influxdb_cpp::query(resp, "SELECT last(\"temperature_celcius\") AS \"last_temperature_celcius\", last(\"humidity_percent\") AS \"last_humidity_percent\", last(\"dry\") AS \"last_dry\", last(\"heat_index_celcius\") AS \"last_heat_index_celcius\", last(\"humidity\") AS \"last_humidity\" FROM \"telegraf\".\"autogen\".\"auto-irrigation\"", serverInfo);
    rapidjson::Document d;
    d.Parse(resp.c_str());
    rapidjson::Value::Array values = d["results"].GetArray()[0]["series"].GetArray()[0]["values"].GetArray()[0].GetArray(); //"last_temperature_celcius",
    int dry = (int) values[3].GetFloat(); //"last_heat_index_celcius",
    int humidity = (int) values[5].GetFloat(); //"last_humidity"

    return GroundHumiditySensorData("HumiditySensor", humidity, dry == 1);
}

static TemperatureSensorData retrieveTemperatureSensorData() {
    // query from table
    influxdb_cpp::server_info serverInfo("127.0.0.1", 8086, "", "test", "test");
    string resp;
    influxdb_cpp::query(resp, "SELECT last(\"temperature_celcius\") AS \"last_temperature_celcius\", last(\"humidity_percent\") AS \"last_humidity_percent\", last(\"dry\") AS \"last_dry\", last(\"heat_index_celcius\") AS \"last_heat_index_celcius\", last(\"humidity\") AS \"last_humidity\" FROM \"telegraf\".\"autogen\".\"auto-irrigation\"", serverInfo);
    rapidjson::Document d;
    d.Parse(resp.c_str());
    rapidjson::Value::Array values = d["results"].GetArray()[0]["series"].GetArray()[0]["values"].GetArray()[0].GetArray();
    float temperature_celcius = values[1].GetFloat(); //"last_temperature_celcius",
    float humidity_percent = values[2].GetFloat(); //"last_humidity_percent",
    float heat_index_celcius = values[4].GetFloat(); //"last_dry",

    return TemperatureSensorData("TemperatureSensor", (int) humidity_percent, (int) temperature_celcius, (int) heat_index_celcius);
}

static MeteoData retrieveMeteoData() {
    return MeteoData("Cachan", 22, 26, 14, 50);
}

#endif //PANELS_PANELS_H
