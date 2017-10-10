#ifndef GAUSSBLUR_H
#define GAUSSBLUR_H

#include "imageprocessor.h"
#include "src/number.h"

class GaussianBlur : public ImageProcessor
{
public:
    GaussianBlur(double sigma, uint8 kernelSize);
    virtual ~GaussianBlur();

    virtual void process(Image &image);
private:
    double sigma;
    uint8 kernelSize;
};

#endif // GAUSSBLUR_H
