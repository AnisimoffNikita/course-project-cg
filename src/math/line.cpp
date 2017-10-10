#include "line.h"

Line::Line()
{
}

Line::Line(const Point &p1, const Point &p2) :
    p1(p1),
    p2(p2)
{
}

Point Line::getP1() const
{
    return p1;
}

void Line::setP1(const Point &value)
{
    p1 = value;
}

Point Line::getP2() const
{
    return p2;
}

void Line::setP2(const Point &value)
{
    p2 = value;
}
