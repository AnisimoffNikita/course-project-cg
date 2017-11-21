#ifndef SIZECALCULATORBASE_H
#define SIZECALCULATORBASE_H

#include <vector>
#include <utility>

#include "src/math/line.h"
#include "src/math/cylindersize.h"

class CylinderSizeCalculatorBase
{
public:
    virtual ~CylinderSizeCalculatorBase();

    virtual CylinderSize evaluate(const std::vector<Line> &lines) = 0;
    virtual void calibrate(const std::vector<Line> &lines, double distance,
                           double radius, double height) = 0;
    virtual void calibrate(double daig, double diagPx) = 0;
};

#endif // SIZECALCULATORBASE_H
