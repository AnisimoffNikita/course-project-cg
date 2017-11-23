#ifndef CANNYEDGEDETECTOR_H
#define CANNYEDGEDETECTOR_H

#include "edgedetector.h"
#include "src/image/grayscaleimage.h"

class CannyEdgeDetector : public EdgeDetector
{
public:
    CannyEdgeDetector(int minThresh = 80, int maxThresh = 100);
    virtual ~CannyEdgeDetector();

    virtual void process(Image &image);

    int getGaussKernelSize() const;
    void setGaussKernelSize(int value);

    float getGaussSigma() const;
    void setGaussSigma(float value);

    int getMinThresh() const;
    void setMinThresh(int value);

    int getMaxThresh() const;
    void setMaxThresh(int value);

private:
    void gradients();
    void nonMaxSuppression();
    void floatThreshold();
    void hysteresis();
    void hysteresisRecursive(uint32 y, uint32 x);

    int minThresh;
    int maxThresh;

    GrayscaleImage image;
    GrayscaleImage directions;
};

#endif // CANNYEDGEDETECTOR_H
