#ifndef PANELS_TEMPERATURELINE_H
#define PANELS_TEMPERATURELINE_H

#include <string>
#include <canvas.h>
#include <graphics.h>
#include <matrix-ui/shape/TextLine.h>
#include <matrix-ui/Layout.h>

class TemperatureLine : public TextLine {
public:
    TemperatureLine(const string& id, const string& label, int temperature, const rgb_matrix::Font *font,
                    int width, int height,
                    int x_offset = 0, int y_offset = 0, const Layout &layout = DEFAULT_LAYOUT);

    virtual ~TemperatureLine();

};


#endif //PANELS_TEMPERATURELINE_H
