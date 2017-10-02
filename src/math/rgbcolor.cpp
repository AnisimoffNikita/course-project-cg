#include "rgbcolor.h"

RGBColor::RGBColor():
    r(0),
    g(0),
    b(0)
{
}

RGBColor::RGBColor(uint8 r, uint8 g, uint8 b):
    r(r),
    g(g),
    b(b)
{
}

uint8 RGBColor::getR() const
{
    return r;
}

void RGBColor::setR(const uint8 &value)
{
    r = value;
}

uint8 RGBColor::getG() const
{
    return g;
}

void RGBColor::setG(const uint8 &value)
{
    g = value;
}

uint8 RGBColor::getB() const
{
    return b;
}

void RGBColor::setB(const uint8 &value)
{
    b = value;
}
