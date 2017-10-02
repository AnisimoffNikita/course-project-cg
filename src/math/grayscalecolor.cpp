#include "grayscalecolor.h"

GrayscaleColor::GrayscaleColor()
{

}

GrayscaleColor::GrayscaleColor(uint8 g):
    g(g)
{

}

uint8 GrayscaleColor::getG() const
{
    return g;
}

void GrayscaleColor::setG(const uint8 &value)
{
    g = value;
}
