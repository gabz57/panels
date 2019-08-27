#ifndef LAYOUT_H
#define LAYOUT_H

#include <string>

class Layout {


public:
    static const std::string FLOAT_LEFT;
    static const std::string FLOAT_RIGHT;
    static const Layout FLOAT_LEFT_LAYOUT ;
    static const Layout FLOAT_RIGHT_LAYOUT;

    Layout(std::string floating);

    virtual ~Layout();

    std::string getFloating() const;

private:
    std::string floating;
};



#endif /* LAYOUT_H */

