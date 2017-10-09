#ifndef CANNYEDGEDETECTOR_H
#define CANNYEDGEDETECTOR_H

#include "edgedetector.h"
#include "src/image/grayscaleimage.h"

class CannyEdgeDetector : public EdgeDetector
{
public:
    CannyEdgeDetector();
    virtual ~CannyEdgeDetector();

    virtual void process(Image &image);

private:
    void gaussianBlur(int kernelSize);
    void gradients();
    void nonMaxSuppression();
    void doubleThreshold();
    void hysteresis();
    void hysteresisRecursive(uint32 y, uint32 x);

    GrayscaleImage image;
    GrayscaleImage directions;
};

#endif // CANNYEDGEDETECTOR_H
