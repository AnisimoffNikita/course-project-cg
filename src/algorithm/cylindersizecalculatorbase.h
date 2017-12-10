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
    virtual bool calibrate(const std::vector<Line> &lines, float distance,
                           float radius, float height) = 0;
    virtual bool calibrate(float distance, float scale) = 0;
};

#endif // SIZECALCULATORBASE_H
