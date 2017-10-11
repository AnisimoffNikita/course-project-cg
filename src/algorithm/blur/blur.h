#ifndef BLUR_H
#define BLUR_H

#include "src/image/image.h"

class Blur
{
public:
    virtual ~Blur();

    virtual void process(Image &image) = 0;
};

#endif // BLUR_H
