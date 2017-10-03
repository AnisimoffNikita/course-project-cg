#ifndef COLOR_H
#define COLOR_H

#include "src/number.h"

class Color
{
public:
    Color();
    Color(uint8 r, uint8 g, uint8 b);

    uint8 red() const;
    void setRed(uint8 value);

    uint8 green() const;
    void setGreen(uint8 value);

    uint8 blue() const;
    void setBlue(uint8 value);

private:
    uint8 r, g, b;
};

#endif // COLOR_H
