#include <iostream>
#include <led-matrix.h>
#include <panels/panels.h>
#include <panels/demoAnimation.h>
#include <panels/meteoAnimation.h>
#include <panels/clockAnimation.h>
#include <matrix-ui/RootPanel.h>
#include <matrix-ui/CanvasHolder.h>
#include <matrix-ui/animation/AnimationComponent.h>

#include <unistd.h>
#include <cstdio>
#include <csignal>

using namespace std;

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

// to use in main while loop

static void InterruptHandler(int signo) {
    interrupt_received = true;
}


RGBMatrix *createMatrix(int argc, char **argv) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm";
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 4;
    defaults.pixel_mapper_config = "U-mapper;Rotate:180";
    defaults.parallel = 1;
    defaults.show_refresh_rate = true;
    return rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
}

int runPanels(int argc, char **argv) {
    RGBMatrix *matrix = createMatrix(argc, argv);

    if (matrix == NULL) {
        std::cout << "Canvas is NULL" << std::endl;
        return 1;
    }

    int panelWidth = matrix->width();
    int panelHeight = matrix->height();

    /*
     * Load font. This needs to be a filename with a bdf bitmap font.
     */
    const char *bdf_font_file = "/home/pi/Desktop/leds/rpi-rgb-led-matrix/fonts/5x7.bdf";
    rgb_matrix::Font *font = new Font();
    if (!font->LoadFont(bdf_font_file)) {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
        return 1;
    }

    int lineHeight = font->height() + 1;
    int lineWidth = panelWidth;

    CanvasHolder canvasHandler(matrix);
    RootPanel *sensorPanel = nullptr;
    RootPanel *meteoPanel = nullptr;

    cout << "Drawing BEGIN" << endl;
    for (int i = 0; i < 100; ++i) {
        delete sensorPanel;
        sensorPanel = new RootPanel("sensorPanel", panelWidth, panelHeight, canvasHandler,
                                    buildSensorPanel(font, panelWidth, panelHeight, lineHeight, lineWidth));

        cout << "Drawing Sensors ..." << endl;
        sensorPanel->render();
        cout << "Drawing Sensors DONE" << endl;

        sleep(8);

        delete meteoPanel;
        meteoPanel = new RootPanel("meteoPanel", panelWidth, panelHeight, canvasHandler,
                                   buildMeteoPanel(font, panelWidth, panelHeight, lineHeight, lineWidth));
        cout << "Drawing Meteo..." << endl;
        meteoPanel->render();
        cout << "Drawing Meteo DONE" << endl;

        sleep(8);
    }

    // Animation finished. Shut down the RGB matrix.
    matrix->Clear();
    delete sensorPanel;
    delete meteoPanel;
    delete matrix;
    delete font;
    return 0;
}

int runAnimatedPanels(int argc, char **argv) {
    RGBMatrix *matrix = createMatrix(argc, argv);

    if (matrix == NULL) {
        std::cout << "Canvas is NULL" << std::endl;
        return 1;
    }

    int panelWidth = matrix->width();
    int panelHeight = matrix->height();

    /*
     * Load font. This needs to be a filename with a bdf bitmap font.
     */
    const char *bdf_font_file = "/home/pi/Desktop/leds/rpi-rgb-led-matrix/fonts/5x7.bdf";
    rgb_matrix::Font *font = new Font();
    if (!font->LoadFont(bdf_font_file)) {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
        return 1;
    }
    int lineHeight = font->height() + 1;
    int lineWidth = panelWidth;

    CanvasHolder canvasHandler(matrix);

//    RootPanel animationRootPanel = RootPanel("demoAnimationRootPanel", panelWidth, panelHeight, canvasHandler,
//                                             buildDemoAnimationPanel(font, panelWidth, panelHeight, lineHeight,
//                                                                     lineWidth));

    RootPanel animationRootPanel = RootPanel("clockAnimationRootPanel", panelWidth, panelHeight, canvasHandler,
                                            buildClockAnimationPanel(panelWidth, panelHeight));

    int fps = 30;
    int usleepTime = 1000000 / fps;
    cout << "Drawing animation ..." << endl;
    while (!interrupt_received) {
        tmillis_t start_wait_ms = GetTimeInMillis();
        animationRootPanel.render();
        tmillis_t time_already_spent = GetTimeInMillis() - start_wait_ms;
        usleep(usleepTime - time_already_spent / 1000);
    }

    cout << "Drawing animation DONE" << endl;

    // Animation finished. Shut down the RGB matrix.
    matrix->Clear();
    delete matrix;
    delete font;
    return 0;
}

int main(int argc, char **argv) {
    char hostname[255];
    memset(hostname, 0, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));

    std::cout << "Hi, " << hostname << "!" << std::endl;

    // It is always good to set up a signal handler to cleanly exit when we
    // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
    // for that.
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);


//    runPanels(argc, argv);
    runAnimatedPanels(argc, argv);

    std::cout << "Bye, " << hostname << "!" << std::endl;
    return 0;
}
