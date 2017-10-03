#ifndef CANNYEDGEDETECTOR_H
#define CANNYEDGEDETECTOR_H

#include "edgedetector.h"

class CannyEdgeDetector : public EdgeDetector
{
public:
    CannyEdgeDetector();
    virtual ~CannyEdgeDetector();

    virtual Image process(const Image &image);

private:

};

#endif // CANNYEDGEDETECTOR_H
