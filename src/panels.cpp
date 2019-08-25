#include <cstdlib>
#include <iostream>
#include <cstring>
#include <led-matrix.h>
#include <Panel.h>
#include <RootPanel.h>
#include <Layout.h>
#include <Text.h>

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
    canvas->Fill(0, 0, 255);

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

static void DrawOnCanvas2(Canvas *canvas) {
    MeteoData origMeteoData("Cachan", 22, 26, 14, 50);

    const MeteoData &meteoData = origMeteoData;

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
    Layout floatLeftLayout = Layout(Layout::FLOAT_LEFT);
    Layout floatRightLayout = Layout(Layout::FLOAT_RIGHT);

    Text cityLabel = Text("cityLabel", floatLeftLayout, meteoData.city, font);
    Text cityTempLabel = Text("cityTempLabel", floatLeftLayout, "Température :", font);
    Text cityTempValue = Text("cityTempValue", floatRightLayout, std::to_string(meteoData.cityTemperature) + "°C", font,
                              5, 0);
    Text minTempLabel = Text("minTempLabel", floatLeftLayout, "Min :", font);
    Text minTempValue = Text("minTempValue", floatRightLayout, std::to_string(meteoData.minTemperature) + "°C", font, 5,
                             0);
    Text maxTempLabel = Text("maxTempLabel", floatLeftLayout, "Max :", font);
    Text maxTempValue = Text("maxTempValue", floatRightLayout, std::to_string(meteoData.maxTemperature) + "°C", font, 5,
                             0);
    Text humidityLabel = Text("humidityLabel", floatLeftLayout, "Humidity :", font);
    Text humidityValue = Text("humidityValue", floatRightLayout, std::to_string(meteoData.humidity) + "%", font);

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
    rootPanel.draw(*canvas);

    sleep(10000);
    std::cout << "Drawing DONE" << std::endl;
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
    defaults.pixel_mapper_config = "U-mapper";
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
    DrawOnCanvas2(canvas);
    DrawOnCanvas(canvas); // Using the canvas.

    // Animation finished. Shut down the RGB matrix.
    canvas->Clear();
    delete canvas;
    std::cout << "Bye, " << hostname << "!" << std::endl;

    return 0;
}