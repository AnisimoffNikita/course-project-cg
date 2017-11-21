#include "cylindersize.h"

CylinderSize::CylinderSize(double height, double radius) :
    height(height),
    radius(radius)
{
}

double CylinderSize::getRadius() const
{
    return radius;
}

void CylinderSize::setRadius(double value)
{
    radius = value;
}

double CylinderSize::getHeight() const
{
    return height;
}

void CylinderSize::setHeight(double value)
{
    height = value;
}
