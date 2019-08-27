#include <cstdlib>
#include <iostream>
#include <cstring>
#include <led-matrix.h>
#include <Panel.h>
#include <panels/panels.h>
#include <RootPanel.h>
#include <Layout.h>
#include <Text.h>

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

#include "influxdb.hpp"

using namespace std;

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
    interrupt_received = true;
}

static void DrawOnCanvas(Canvas *canvas) {
    /*
     * Let's create a simple animation. We use the canvas to draw
     * pixels. We wait between each step to have a slower animation.
     */
//    canvas->Fill(0, 0, 255);

    int center_x = canvas->width() / 2;
    int center_y = canvas->height() / 2;
    float radius_max = canvas->width() / 2;
    float angle_step = 1.0 / 360;
    for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step) {
        if (interrupt_received)
            return;
        float dot_x = cos(a * 2 * M_PI) * r;
        float dot_y = sin(a * 2 * M_PI) * r;
        canvas->SetPixel(center_x + dot_x, center_y + dot_y, 255, 0, 0);
        usleep(1 * 1000); // wait a little to slow down things.
    }
}

static MeteoData retrieveMeteoData() {
    // query from table
//    influxdb_cpp::server_info serverInfo("127.0.0.1", 8086, "", "test", "test");
////    string resp;
////    influxdb_cpp::query(resp, "show databases", serverInfo);
////    cout << "show databases: " << resp << endl;
////    influxdb_cpp::query(resp, "show databases", serverInfo);
////    cout << "WAAAAAAAAAA" << resp << "WAAAAAAAAAA" << endl;
    return MeteoData("Cachan", 22, 26, 14, 50);
}

static GroundHumiditySensorData retrieveGroundHumiditySensorData() {
    return GroundHumiditySensorData("HumiditySensor", 457, true);
}

static TemperatureSensorData retrieveTemperatureSensorData() {
    return TemperatureSensorData("TemperatureSensor", 55, 20, 21);
}

static void DrawMeteo(Canvas *canvas) {
    const MeteoData meteoData = retrieveMeteoData();
    /*
     * Load font. This needs to be a filename with a bdf bitmap font.
     */
    const char *bdf_font_file = "/home/pi/Desktop/leds/rpi-rgb-led-matrix/fonts/5x7.bdf";
    rgb_matrix::Font font;
    if (!font.LoadFont(bdf_font_file)) {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
//        return 1;
        return;
    }

    Text cityLabel = Text("cityLabel", Layout::FLOAT_LEFT_LAYOUT, meteoData.city, font);
    Text cityTempLabel = Text("cityTempLabel", Layout::FLOAT_LEFT_LAYOUT, "Température :", font);
    Text cityTempValue = Text("cityTempValue", Layout::FLOAT_RIGHT_LAYOUT, std::to_string(meteoData.cityTemperature) + "°C", font,
                              5, 0);
    Text minTempLabel = Text("minTempLabel", Layout::FLOAT_LEFT_LAYOUT, "Min :", font);
    Text minTempValue = Text("minTempValue", Layout::FLOAT_RIGHT_LAYOUT, std::to_string(meteoData.minTemperature) + "°C", font, 5,
                             0);
    Text maxTempLabel = Text("maxTempLabel", Layout::FLOAT_LEFT_LAYOUT, "Max :", font);
    Text maxTempValue = Text("maxTempValue", Layout::FLOAT_RIGHT_LAYOUT, std::to_string(meteoData.maxTemperature) + "°C", font, 5,
                             0);
    Text humidityLabel = Text("humidityLabel", Layout::FLOAT_LEFT_LAYOUT, "Humidity :", font);
    Text humidityValue = Text("humidityValue", Layout::FLOAT_RIGHT_LAYOUT, std::to_string(meteoData.humidity) + "%", font);

    int PANEL_WIDTH = 128;
    int PANEL_HEIGHT = 128;
    int LINE_HEIGHT = 10;
    int LINE_WIDTH = 128;

    Panel meteoPanel = Panel("meteoPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);
    Panel cityLine = Panel("cityLine", PANEL_WIDTH, LINE_HEIGHT, 0, 0);
    cityLine.addComponent(&cityLabel);
    meteoPanel.addComponent(&cityLine);

    Panel cityTempLine = Panel("cityTempLine", LINE_WIDTH, LINE_HEIGHT, 0, LINE_HEIGHT);
    cityTempLine.addComponent(&cityTempLabel);
    cityTempLine.addComponent(&cityTempValue);
    meteoPanel.addComponent(&cityTempLine);

    Panel minTempLine = Panel("minTempLine", LINE_WIDTH, LINE_HEIGHT, 0, 2 * LINE_HEIGHT);
    minTempLine.addComponent(&minTempLabel);
    minTempLine.addComponent(&minTempValue);
    meteoPanel.addComponent(&minTempLine);

    Panel maxTempLine = Panel("maxTempLine", LINE_WIDTH, LINE_HEIGHT, 0, 3 * LINE_HEIGHT);
    maxTempLine.addComponent(&maxTempLabel);
    maxTempLine.addComponent(&maxTempValue);
    meteoPanel.addComponent(&maxTempLine);

    Panel humidityLine = Panel("humidity", LINE_WIDTH, LINE_HEIGHT, 0, 4 * LINE_HEIGHT);
    humidityLine.addComponent(&humidityLabel);
    humidityLine.addComponent(&humidityValue);
    meteoPanel.addComponent(&humidityLine);

    RootPanel rootPanel = RootPanel("rootPanel", PANEL_WIDTH, PANEL_HEIGHT, meteoPanel);

    std::cout << "Drawing ..." << std::endl;
//    canvas->Fill(0, 0, 255);
    rootPanel.draw(*canvas);
    std::cout << "Drawing DONE" << std::endl;
}

static void DrawSensors(Canvas *canvas) {
    std::cout << "Drawing Sensors BEGIN" << std::endl;

    /*
     * Load font. This needs to be a filename with a bdf bitmap font.
     */
    const char *bdf_font_file = "/home/pi/Desktop/leds/rpi-rgb-led-matrix/fonts/5x7.bdf";
    rgb_matrix::Font font;
    if (!font.LoadFont(bdf_font_file)) {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
//        return 1;
        return;
    }


    const GroundHumiditySensorData groundHumiditySensorData = retrieveGroundHumiditySensorData();
    const TemperatureSensorData temperatureSensorData = retrieveTemperatureSensorData();

    int PANEL_WIDTH = 128;
    int PANEL_HEIGHT = 128;
    int LINE_HEIGHT = 8;
    int LINE_WIDTH = 128;

    Panel sensorPanel = Panel("sensorPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);


    //// HUMIDITÉ
    std::cout << "Drawing Sensors assembling panel humidity" << std::endl;
    Panel groundHumiditySensorPanel = Panel("groundHumiditySensor", PANEL_WIDTH, PANEL_HEIGHT / 2, 0, 0);

    Text title = Text("title", Layout::FLOAT_LEFT_LAYOUT, "Capteurs :", font);
    Text lineOfEquals = Text("lineOfEquals", Layout::FLOAT_LEFT_LAYOUT, "----------", font);

    Text groundHumiditySensor = Text("groundHumiditySensor", Layout::FLOAT_LEFT_LAYOUT, "Humidité plante :", font);
    Text groundHumiditySensorName = Text("groundHumiditySensorName", Layout::FLOAT_LEFT_LAYOUT, groundHumiditySensorData.name,
                                         font);
    Text groundHumidityLabel = Text("groundHumidityLabel", Layout::FLOAT_LEFT_LAYOUT, "Humidité :", font);
    Text groundHumidityValue = Text("groundHumidityValue", Layout::FLOAT_RIGHT_LAYOUT,
                                    std::to_string(groundHumiditySensorData.humidity) + ".", font);
    Text groundDryLabel = Text("groundDryLabel", Layout::FLOAT_LEFT_LAYOUT, "Sécheresse :", font);
    Text groundDryValue = Text("groundDryValue", Layout::FLOAT_RIGHT_LAYOUT, (groundHumiditySensorData.dry ? "OUI" : "NON"),
                               font);

    Panel titleLine = Panel("titleLine", PANEL_WIDTH, LINE_HEIGHT, 0, 0);
    titleLine.addComponent(&title);
    groundHumiditySensorPanel.addComponent(&titleLine);

    Panel equalsLine = Panel("equalsLine", PANEL_WIDTH, LINE_HEIGHT, 0, LINE_HEIGHT);
    equalsLine.addComponent(&lineOfEquals);
    groundHumiditySensorPanel.addComponent(&equalsLine);

    Panel groundHumiditySensorLine = Panel("groundHumiditySensor", LINE_WIDTH, LINE_HEIGHT, 0, 3*LINE_HEIGHT);
    groundHumiditySensorLine.addComponent(&groundHumiditySensor);
    groundHumiditySensorPanel.addComponent(&groundHumiditySensorLine);

    Panel groundHumiditySensorNameLine = Panel("groundHumiditySensorName", LINE_WIDTH, LINE_HEIGHT, 0, 4 * LINE_HEIGHT);
    groundHumiditySensorNameLine.addComponent(&groundHumiditySensorName);
    groundHumiditySensorPanel.addComponent(&groundHumiditySensorNameLine);

    Panel groundHumidityLine = Panel("groundHumidityLine", LINE_WIDTH, LINE_HEIGHT, 0, 5 * LINE_HEIGHT);
    groundHumidityLine.addComponent(&groundHumidityLabel);
    groundHumidityLine.addComponent(&groundHumidityValue);
    groundHumiditySensorPanel.addComponent(&groundHumidityLine);

    Panel groundDryLine = Panel("groundDryLine", LINE_WIDTH, LINE_HEIGHT, 0, 6 * LINE_HEIGHT);
    groundDryLine.addComponent(&groundDryLabel);
    groundDryLine.addComponent(&groundDryValue);
    groundHumiditySensorPanel.addComponent(&groundDryLine);

    sensorPanel.addComponent(&groundHumiditySensorPanel);

    //// TEMPERATURE
    std::cout << "Drawing Sensors assembling panel temperature" << std::endl;
    Panel temperatureSensorPanel = Panel("temperatureSensor", PANEL_WIDTH, PANEL_HEIGHT / 2, 0, PANEL_HEIGHT / 2);

    Text temperatureSensor = Text("temperatureSensor", Layout::FLOAT_LEFT_LAYOUT, "Température pièce :", font);
    Text lineOfEquals2 = Text("lineOfEquals2", Layout::FLOAT_LEFT_LAYOUT, "-------------------", font);
    Text temperatureSensorName = Text("temperatureSensorName", Layout::FLOAT_LEFT_LAYOUT, temperatureSensorData.name, font);
    Text temperatureLabel = Text("temperatureLabel", Layout::FLOAT_LEFT_LAYOUT, "Température :", font);
    Text temperatureValue = Text("temperatureValue", Layout::FLOAT_RIGHT_LAYOUT,
                                 std::to_string(temperatureSensorData.temperatureCelcius) + "°C", font, 5, 0);
    Text heatIndexLabel = Text("heatIndexLabel", Layout::FLOAT_LEFT_LAYOUT, "Indice de chaleur :", font);
    Text heatIndexValue = Text("heatIndexValue", Layout::FLOAT_RIGHT_LAYOUT,
                               std::to_string(temperatureSensorData.heatIndexCelcius) + "°C", font, 5, 0);
    Text humidityLabel = Text("humidityLabel", Layout::FLOAT_LEFT_LAYOUT, "Humidité :", font);
    Text humidityValue = Text("humidityValue", Layout::FLOAT_RIGHT_LAYOUT, std::to_string(temperatureSensorData.humidity) + "%",
                              font);
    Panel temperatureSensorLine = Panel("temperatureSensor", LINE_WIDTH, LINE_HEIGHT, 0, 0);
    temperatureSensorLine.addComponent(&temperatureSensor);
    temperatureSensorPanel.addComponent(&temperatureSensorLine);

    Panel equalsLine2 = Panel("equalsLine2", PANEL_WIDTH, LINE_HEIGHT, 0, LINE_HEIGHT);
    equalsLine2.addComponent(&lineOfEquals2);
    temperatureSensorPanel.addComponent(&equalsLine2);

    Panel temperatureSensorNameLine = Panel("temperatureSensorName", LINE_WIDTH, LINE_HEIGHT, 0, 3 * LINE_HEIGHT);
    temperatureSensorNameLine.addComponent(&temperatureSensorName);
    temperatureSensorPanel.addComponent(&temperatureSensorNameLine);

    Panel temperatureLine = Panel("temperature", LINE_WIDTH, LINE_HEIGHT, 0, 5 * LINE_HEIGHT);
    temperatureLine.addComponent(&temperatureLabel);
    temperatureLine.addComponent(&temperatureValue);
    temperatureSensorPanel.addComponent(&temperatureLine);

    Panel heatIndexLine = Panel("heatIndex", LINE_WIDTH, LINE_HEIGHT, 0, 6 * LINE_HEIGHT);
    heatIndexLine.addComponent(&heatIndexLabel);
    heatIndexLine.addComponent(&heatIndexValue);
    temperatureSensorPanel.addComponent(&heatIndexLine);

    Panel humidityLine = Panel("humidity", LINE_WIDTH, LINE_HEIGHT, 0, 7 * LINE_HEIGHT);
    humidityLine.addComponent(&humidityLabel);
    humidityLine.addComponent(&humidityValue);
    temperatureSensorPanel.addComponent(&humidityLine);

    sensorPanel.addComponent(&temperatureSensorPanel);


    RootPanel rootPanel = RootPanel("rootPanel", PANEL_WIDTH, PANEL_HEIGHT, sensorPanel);

    std::cout << "Drawing Sensors ..." << std::endl;
//    canvas->Fill(0, 0, 255);
    rootPanel.draw(*canvas);
    std::cout << "Drawing Sensors DONE" << std::endl;
}


/*
 *
 */
int main(int argc, char **argv) {
    char hostname[255];
    memset(hostname, 0, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));

    std::cout << "Hi, " << hostname << "!" << std::endl;

    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm"; // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 4;
    defaults.pixel_mapper_config = "U-mapper;Rotate:180";
    defaults.parallel = 1;
//    defaults.show_refresh_rate = true;
    Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL) {
        std::cout << "Canvas is NULL" << std::endl;
        return 1;
    }

    // It is always good to set up a signal handler to cleanly exit when we
    // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
    // for that.
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    for (int i = 0; i < 100; ++i) {
        std::cout << "Drawing 1" << std::endl;
        canvas->Clear();
        DrawMeteo(canvas);
        sleep(8);
        std::cout << "Drawing 2" << std::endl;
        canvas->Clear();
        DrawSensors(canvas);
        sleep(8);
    }
    std::cout << "Drawing DONE, BYE" << std::endl;
//    DrawOnCanvas(canvas); // Using the canvas.

    // Animation finished. Shut down the RGB matrix.
    canvas->Clear();
    delete canvas;
    std::cout << "Bye, " << hostname << "!" << std::endl;

    return 0;
}