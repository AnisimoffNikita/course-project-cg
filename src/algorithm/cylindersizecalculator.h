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
    virtual void calibrate(const std::vector<Line> &lines, double distance, double radius, double height);
private:
    void findEdges();
    void calculateSize();

    Lines lines;
    CylinderSize size;

    double distance;
    double factor;
};

#endif // SIZECALCULATOR_H
