#include "color.h"

Color::Color():
    r(0),
    g(0),
    b(0)
{
}

Color::Color(uint8 r, uint8 g, uint8 b):
    r(r),
    g(g),
    b(b)
{
}

uint8 Color::getRed() const
{
    return r;
}

void Color::setRed(uint8 value)
{
    r = value;
}

uint8 Color::getGreen() const
{
    return g;
}

void Color::setGreen(uint8 value)
{
    g = value;
}

uint8 Color::getBlue() const
{
    return b;
}

void Color::setBlue(uint8 value)
{
    b = value;
}
