#include "cylindersize.h"

CylinderSize::CylinderSize(float height, float radius) :
    height(height),
    radius(radius)
{
}

float CylinderSize::getRadius() const
{
    return radius;
}

void CylinderSize::setRadius(float value)
{
    radius = value;
}

float CylinderSize::getHeight() const
{
    return height;
}

void CylinderSize::setHeight(float value)
{
    height = value;
}
