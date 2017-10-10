#ifndef LINE_H
#define LINE_H

#include "src/number.h"
#include "point.h"

class Line
{
public:
    Line();
    Line(const Point &p1, const Point &p2);

    Point getP1() const;
    void setP1(const Point &value);

    Point getP2() const;
    void setP2(const Point &value);

private:
    Point p1;
    Point p2;
};

#endif // LINE_H
