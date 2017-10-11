#ifndef HOUGHTRANSFORM_H
#define HOUGHTRANSFORM_H

#include <memory>

#include "linetransform.h"
#include "src/image/grayscaleimage.h"
#include "src/math/point.h"
#include "src/math/line.h"

class HoughTransform : public LineTransform
{
private:
    using Points = std::vector<Point>;
public:
    HoughTransform(uint32 threshold = 50);
    virtual ~HoughTransform();

    virtual void process(Image &){}

    std::vector<Line> process2(Image &image);


private:
    void fillAccumulator();
    void getLines();
    void drawLines(Image &color);

    void brezenhem(Image &color, const Line &line);

    uint32 threshold;
    GrayscaleImage image;

    std::vector<Points> accumulator;
    std::vector<Line> lines;
    uint32 accumulatorWidth, accumulatorHeight;
};

#endif // HOUGHTRANSFORM_H
