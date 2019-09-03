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

int main(int argc, char **argv) {
    char hostname[255];
    memset(hostname, 0, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));

    std::cout << "Hi, " << hostname << "!" << std::endl;

    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm";
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 4;
    defaults.pixel_mapper_config = "U-mapper;Rotate:180";
    defaults.parallel = 1;
//    defaults.show_refresh_rate = true;
    RGBMatrix *matrix = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
    if (matrix == NULL) {
        std::cout << "Canvas is NULL" << std::endl;
        return 1;
    }

    int panelWidth = 128;
    int panelHeight = 128;
    int lineHeight = 8;
    int lineWidth = 128;

    // It is always good to set up a signal handler to cleanly exit when we
    // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
    // for that.
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    /*
     * Load font. This needs to be a filename with a bdf bitmap font.
     */
    const char *bdf_font_file = "/home/pi/Desktop/leds/rpi-rgb-led-matrix/fonts/5x7.bdf";
    rgb_matrix::Font *font = new Font();
    if (!font->LoadFont(bdf_font_file)) {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
        return 1;
    }

    FrameCanvas *offscreen = matrix->CreateFrameCanvas();

    RootPanel *sensorPanel = nullptr;
    RootPanel *meteoPanel = nullptr;

    cout << "Drawing BEGIN" << endl;
    for (int i = 0; i < 100; ++i) {
        delete sensorPanel;
        sensorPanel = new RootPanel("sensorPanel", panelWidth, panelHeight,
                                    buildSensorPanel(font, panelWidth, panelHeight, lineHeight, lineWidth));

        cout << "Drawing Sensors ..." << endl;
        offscreen->Clear();
        sensorPanel->draw(*offscreen);
        offscreen = matrix->SwapOnVSync(offscreen);
        cout << "Drawing Sensors DONE" << endl;

        sleep(8);

        delete meteoPanel;
        meteoPanel = new RootPanel("meteoPanel", panelWidth, panelHeight,
                                   buildMeteoPanel(font, panelWidth, panelHeight, lineHeight, lineWidth));
        cout << "Drawing Meteo..." << endl;
        offscreen->Clear();
        meteoPanel->draw(*offscreen);
        offscreen = matrix->SwapOnVSync(offscreen);
        cout << "Drawing Meteo DONE" << endl;

        sleep(8);
    }

    // Animation finished. Shut down the RGB matrix.
    matrix->Clear();
    delete sensorPanel;
    delete meteoPanel;
    delete matrix;
    delete font;
    std::cout << "Bye, " << hostname << "!" << std::endl;

    return 0;
}
