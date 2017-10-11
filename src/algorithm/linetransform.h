#ifndef LINETRANSFORM_H
#define LINETRANSFORM_H

#include "src/image/image.h"
#include "src/math/line.h"

class LineTransform
{
public:
    virtual ~LineTransform();

    virtual std::vector<Line> process(Image &image) = 0;
};

#endif // LINETRANSFORM_H
