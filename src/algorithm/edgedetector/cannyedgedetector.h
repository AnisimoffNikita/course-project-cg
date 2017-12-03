#ifndef CANNYEDGEDETECTOR_H
#define CANNYEDGEDETECTOR_H

#include "edgedetector.h"
#include "src/image/grayscaleimage.h"
#include "src/number.h"

class CannyEdgeDetector : public EdgeDetector
{
public:
    CannyEdgeDetector(int32 minThresh = 80, int32 maxThresh = 100);
    virtual ~CannyEdgeDetector();

    virtual void process(Image &image);

    int32 getGaussKernelSize() const;
    void setGaussKernelSize(int32 value);

    float getGaussSigma() const;
    void setGaussSigma(float value);

    int32 getMinThresh() const;
    void setMinThresh(int32 value);

    int32 getMaxThresh() const;
    void setMaxThresh(int32 value);

private:
    void gradients();
    void nonMaxSuppression();
    void floatThreshold();
    void hysteresis();
    void hysteresisRecursive(uint32 y, uint32 x);

    int32 minThresh;
    int32 maxThresh;

    GrayscaleImage image;
    GrayscaleImage directions;
};

#endif // CANNYEDGEDETECTOR_H
