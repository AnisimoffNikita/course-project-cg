#ifndef GRAYSCALECONVERTER_H
#define GRAYSCALECONVERTER_H

#include "imageprocessor.h"

class GrayscaleConverter : public ImageProcessor
{
public:
    GrayscaleConverter();
    virtual ~GrayscaleConverter();
    virtual void process(Image &image);
protected:
    Color getGrayscale(const Color &color);
};

#endif // GRAYSCALECONVERTER_H
