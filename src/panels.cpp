#include <cstdlib>
#include <iostream>
#include <cstring>
#include <led-matrix.h>
#include <panels/panels.h>
#include <matrix-ui/Panel.h>
#include <matrix-ui/RootPanel.h>
#include <matrix-ui/Text.h>
#include <matrix-ui/TemperatureLine.h>
#include <matrix-ui/TextLine.h>

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
    rgb_matrix::Font *font = new Font();
    if (!font->LoadFont(bdf_font_file)) {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
//        return 1;
        return;
    }

    int PANEL_WIDTH = 128;
    int PANEL_HEIGHT = 128;
    int LINE_HEIGHT = 10;
    int LINE_WIDTH = 128;

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
    meteoPanel->addComponent(new TextLine("humidity", "Humidité :", std::to_string(meteoData.humidity) + "%",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 4 * LINE_HEIGHT));

    RootPanel *rootPanel = new RootPanel("rootPanel", PANEL_WIDTH, PANEL_HEIGHT, meteoPanel);

    std::cout << "Drawing ..." << std::endl;
//    canvas->Fill(0, 0, 255);
    rootPanel->draw(*canvas);
    sleep(8);
    std::cout << "Drawing DONE" << std::endl;
    delete rootPanel;
    std::cout << "delete DONE" << std::endl;
}

static void DrawSensors(Canvas *canvas) {
    std::cout << "Drawing Sensors BEGIN" << std::endl;

    /*
     * Load font. This needs to be a filename with a bdf bitmap font.
     */
    const char *bdf_font_file = "/home/pi/Desktop/leds/rpi-rgb-led-matrix/fonts/5x7.bdf";
    rgb_matrix::Font *font = new Font();
    if (!font->LoadFont(bdf_font_file)) {
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

    Panel *mainPanel = new Panel("sensorPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);

    //// BLOC HUMIDITÉ
    std::cout << "Drawing Sensors assembling panel humidity" << std::endl;
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
            new TextLine("groundHumidityLine", "Humidité :", std::to_string(groundHumiditySensorData.humidity) + ".",
                         font, LINE_WIDTH, LINE_HEIGHT, 0, 5 * LINE_HEIGHT));
    upperPanel->addComponent(new TextLine("groundDryLine", "Sécheresse :", groundHumiditySensorData.dry ? "OUI" : "NON",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 6 * LINE_HEIGHT));

    mainPanel->addComponent(upperPanel);

    //// BLOC TEMPERATURE
    std::cout << "Drawing Sensors assembling panel temperature" << std::endl;
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
                                          std::to_string(temperatureSensorData.humidity) + "%",
                                          font, LINE_WIDTH, LINE_HEIGHT, 0, 7 * LINE_HEIGHT));

    mainPanel->addComponent(lowerPanel);

    RootPanel *rootPanel = new RootPanel("rootPanel", PANEL_WIDTH, PANEL_HEIGHT, mainPanel);

    std::cout << "Drawing Sensors ..." << std::endl;
//    canvas->Fill(0, 0, 255);
    rootPanel->draw(*canvas);
    sleep(8);
    std::cout << "Drawing Sensors DONE" << std::endl;
    delete rootPanel;
    std::cout << "delete DONE" << std::endl;
}

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
        std::cout << "Drawing 2" << std::endl;
        canvas->Clear();
        DrawSensors(canvas);
    }
    std::cout << "Drawing DONE, BYE" << std::endl;
//    DrawOnCanvas(canvas); // Using the canvas.

    // Animation finished. Shut down the RGB matrix.
    canvas->Clear();
    delete canvas;
    std::cout << "Bye, " << hostname << "!" << std::endl;

    return 0;
}