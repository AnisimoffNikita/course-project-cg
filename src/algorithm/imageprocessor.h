#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "src/image/image.h"

class ImageProcessor
{
public:
    virtual ~ImageProcessor();
    virtual void process(Image &image) = 0;
};


#endif // IMAGEPROCESSOR_H
