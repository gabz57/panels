#include "matrix-ui/TemperatureLine.h"
#include "matrix-ui/Text.h"

TemperatureLine::TemperatureLine(std::string id, std::string label, int temperature, rgb_matrix::Font *font,
                                 int width, int height, int x_offset, int y_offset, Layout &layout) :
        Panel(id, width, height, x_offset, y_offset, layout) {
    this->addComponent(new Text(id + "-label", Layout::FLOAT_LEFT_LAYOUT, label, font));
    this->addComponent(new Text(id + "-value", Layout::FLOAT_RIGHT_LAYOUT, std::to_string(temperature) + "°C", font, 5, 0));
}

TemperatureLine::~TemperatureLine() {
}
