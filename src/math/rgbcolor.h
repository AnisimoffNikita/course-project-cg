#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include "src/number.h"

class RGBColor
{
public:
    RGBColor();
    RGBColor(uint8 r, uint8 g, uint8 b);

    uint8 getR() const;
    void setR(const uint8 &value);

    uint8 getG() const;
    void setG(const uint8 &value);

    uint8 getB() const;
    void setB(const uint8 &value);

private:
    uint8 r, g, b;
};

#endif // RGBCOLOR_H
