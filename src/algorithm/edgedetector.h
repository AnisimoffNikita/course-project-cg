#ifndef EDGEDETECTOR_H
#define EDGEDETECTOR_H

#include "src/image/image.h"

class EdgeDetector
{
public:
    virtual ~EdgeDetector();
    virtual Image process(const Image &image) = 0;
};

#endif // EDGEDETECTOR_H
