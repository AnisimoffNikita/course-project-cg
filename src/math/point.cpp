#include "point.h"

Point::Point() :
    x(0),
    y(0)
{

}

Point::Point(int x, int y):
    x(x),
    y(y)
{

}

int32 Point::getX() const
{
    return x;
}

void Point::setX(const int32 &value)
{
    x = value;
}

int32 Point::getY() const
{
    return y;
}

void Point::setY(const int32 &value)
{
    y = value;
}
