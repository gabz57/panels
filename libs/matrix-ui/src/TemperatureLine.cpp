#include "matrix-ui/TemperatureLine.h"
#include "matrix-ui/shape/Text.h"

TemperatureLine::TemperatureLine(const string& id, const string& label, int temperature, const rgb_matrix::Font *font,
                                 int width, int height, int x_offset, int y_offset, const Layout &layout) :
        TextLine(id, label, to_string(temperature) + "°C", font, width, height,
                 x_offset, y_offset,
                 layout,
                 0, 0, 5, 0) {}

TemperatureLine::~TemperatureLine() {
}
