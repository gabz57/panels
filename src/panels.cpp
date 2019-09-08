#include <iostream>
#include <led-matrix.h>
#include <panels/panels.h>
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

using namespace std;

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

// to use in main while loop

static void InterruptHandler(int signo) {
    interrupt_received = true;
}

Panel *buildAnimationPanel(const Font *font, int PANEL_WIDTH, int PANEL_HEIGHT, int LINE_HEIGHT, int LINE_WIDTH) {
    Panel *animationPanel = new Panel("animationPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);

    Rectangle *rectangle = new Rectangle("rectangle", 64, 64, 20, 20, -10, -10);
    RotationTransformer *rotationTransformer4 = new RotationTransformer(360, 64, 64);
    AnimationComponent *animComponent5 = new AnimationComponent(rectangle, rotationTransformer4, 360, 2500, true);
    animationPanel->addComponent(animComponent5);

    Rectangle *rectangle2 = new Rectangle("rectangle2", 32, 96, 20, 20, -10, -10);
    VerticalStretchingTransformer *verticalStretchingTransformer = new VerticalStretchingTransformer(0.5, 86, 128);
    AnimationComponent *animComponent6 = new AnimationComponent(rectangle2, verticalStretchingTransformer, 128, 2500, true);
    animationPanel->addComponent(animComponent6);

    Circle *circle = new Circle("circle", 96, 96, 20);
    VerticalStretchingTransformer *verticalStretchingTransformer2 = new VerticalStretchingTransformer(0.5, 86, 128);
    AnimationComponent *animComponent7 = new AnimationComponent(circle, verticalStretchingTransformer2, 128, 2500, true);
    animationPanel->addComponent(animComponent7);

    TextLine *textLine = new TextLine("cityLine", "How are you ?", "Fine ?", font, LINE_WIDTH, LINE_HEIGHT, 0, 0);
    TranslationTransformer *translationTransformer = new TranslationTransformer(20, 20);
    AnimationComponent *animComponent = new AnimationComponent(textLine, translationTransformer, 20, 5000);
    animationPanel->addComponent(animComponent);

    TextLine *textLine2 = new TextLine("cityLine2", "Oh yeah !", "++", font, LINE_WIDTH, LINE_HEIGHT, 0, LINE_HEIGHT);
    TranslationTransformer *translationTransformer2 = new TranslationTransformer(0, 30);
    AnimationComponent *animComponent2 = new AnimationComponent(textLine2, translationTransformer2, 30, 2000);
    animationPanel->addComponent(animComponent2);

//    Text *text = new Text("wordLine", "Oh yeah !", font, DEFAULT_TEXT_LAYOUT, 64, 64);
//    std::list<PixelTransformer *> transformers =  std::list<PixelTransformer *>();
//    transformers.push_back(rotationTransformer);
//    transformers.push_back(translationTransformer3);
    Text *text = new Text("wordLine", "Oh yeah !", font, Text::DEFAULT_TEXT_LAYOUT, 16, 16);
    RotationTransformer *rotationTransformer = new RotationTransformer(360, 16, 16);
    AnimationComponent *subAnimComponent = new AnimationComponent(text, rotationTransformer, 360, 4000);

    TranslationTransformer *translationTransformer3 = new TranslationTransformer(32, 32);
    AnimationComponent *animComponent3 = new AnimationComponent(subAnimComponent, translationTransformer3, 32, 4000);
    RotationTransformer *rotationTransformer2 = new RotationTransformer(360, 64, 64);
    AnimationComponent *parentAnimComponent = new AnimationComponent(animComponent3, rotationTransformer2, 360, 2000);
    animationPanel->addComponent(parentAnimComponent);

    Dot *dot = new Dot("dot", 0, 0);
    Dot *dot2 = new Dot("dot2", 0, 32);
    Dot *dot3 = new Dot("dot3", 0, 46);
    Dot *dot4 = new Dot("dot4", 0, 54);

    Panel *panel = new Panel("secondsPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);
    panel->addComponent(dot);
    panel->addComponent(dot2);
    panel->addComponent(dot3);
    panel->addComponent(dot4);
    RotationTransformer *rotationTransformer3 = new RotationTransformer(4 * 360, 0, 64);
    AnimationComponent *animComponent4 = new AnimationComponent(panel, rotationTransformer3, 4 * 360, 4 * 60000);

    Panel *parentPanel = new Panel("parentPanel", PANEL_WIDTH, PANEL_HEIGHT, 0, 0);
    parentPanel->addComponent(animComponent4);

    animationPanel->addComponent(parentPanel);


    return animationPanel;
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

RGBMatrix *createMatrix(int argc, char **argv) {
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat-pwm";
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 4;
    defaults.pixel_mapper_config = "U-mapper;Rotate:180";
    defaults.parallel = 1;
//    defaults.show_refresh_rate = true;
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

    RootPanel animatedPanelRoot = RootPanel("animationPanel", panelWidth, panelHeight, canvasHandler,
                                            buildAnimationPanel(font, panelWidth, panelHeight, lineHeight, lineWidth));

    int nbSeconds = 60;
    int fps = 30;
    int refreshNb = nbSeconds * fps;
    int usleepTime = 1000000 / fps;
    cout << "Drawing animation ..." << endl;
    while (!interrupt_received) {
//  for (int i = 0; i < refreshNb; i++) {
        tmillis_t start_wait_ms = GetTimeInMillis();
        animatedPanelRoot.render();
        tmillis_t time_already_spent = GetTimeInMillis() - start_wait_ms;
        usleep(usleepTime - time_already_spent / 1000);
    }
    //    canvasHandler.clear();
    //    animatedPanelRoot.draw(canvasHandler);
    //    //canvasHandler.renderAndSwap(); // for static use

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
