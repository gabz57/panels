#ifndef PANELS_TEMPERATURELINE_H
#define PANELS_TEMPERATURELINE_H

#include <string>
#include <canvas.h>
#include <graphics.h>
#include <matrix-ui/Component.h>
#include <matrix-ui/Panel.h>
#include <matrix-ui/Layout.h>

class TemperatureLine : public Panel {
public:
    TemperatureLine(std::string id, std::string label, int temperature, rgb_matrix::Font *font, int width,
                    int height, int x_offset = 0, int y_offset = 0, Layout &layout = DEFAULT_LAYOUT);

    virtual ~TemperatureLine();

};


#endif //PANELS_TEMPERATURELINE_H
