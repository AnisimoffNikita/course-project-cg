#ifndef GRAYSCALECOLOR_H
#define GRAYSCALECOLOR_H

#include "src/number.h"

class GrayscaleColor
{
public:
    GrayscaleColor();
    GrayscaleColor(uint8 g);

    uint8 getG() const;
    void setG(const uint8 &value);

private:
    uint8 g;
};

#endif // GRAYSCALECOLOR_H
