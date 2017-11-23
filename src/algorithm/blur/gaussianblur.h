#ifndef GAUSSBLUR_H
#define GAUSSBLUR_H

#include "blur.h"
#include "src/number.h"

class GaussianBlur : public Blur
{
public:
    GaussianBlur(float sigma = 1.4, uint8 kernelSize = 3);
    virtual ~GaussianBlur();

    virtual void process(Image &image);
    float getSigma() const;
    void setSigma(float value);

    uint8 getKernelSize() const;
    void setKernelSize(const uint8 &value);

private:
    float sigma;
    uint8 kernelSize;
};

#endif // GAUSSBLUR_H
