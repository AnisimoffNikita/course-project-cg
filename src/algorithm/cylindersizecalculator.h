#ifndef SIZECALCULATOR_H
#define SIZECALCULATOR_H

#include "cylindersizecalculatorbase.h"

class CylinderSizeCalculator : public CylinderSizeCalculatorBase
{
private:
    using Lines = std::vector<Line>;
public:
    CylinderSizeCalculator();
    virtual ~CylinderSizeCalculator();

    virtual CylinderSize evaluate(const Lines &lines);
    virtual bool calibrate(const std::vector<Line> &lines, float distance,
                           float radius, float height);
    virtual bool calibrate(float distance, float scale);

private:
    void findEdges();
    void calculateSize();

    Lines lines;
    CylinderSize size;

    float distance;
    float factor;
};

#endif // SIZECALCULATOR_H
