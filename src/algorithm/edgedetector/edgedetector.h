#ifndef EDGEDETECTOR_H
#define EDGEDETECTOR_H

#include "src/image/image.h"

class EdgeDetector
{
public:
    virtual ~EdgeDetector();

    virtual void process(Image &image) = 0;
};

#endif // EDGEDETECTOR_H
