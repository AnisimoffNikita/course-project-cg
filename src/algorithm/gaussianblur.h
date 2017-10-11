#ifndef GAUSSBLUR_H
#define GAUSSBLUR_H

#include "blur.h"
#include "src/number.h"

class GaussianBlur : public Blur
{
public:
    GaussianBlur(double sigma = 1.4, uint8 kernelSize = 3);
    virtual ~GaussianBlur();

    virtual void process(Image &image);
private:
    double sigma;
    uint8 kernelSize;
};

#endif // GAUSSBLUR_H
