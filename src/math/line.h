#ifndef LINE_H
#define LINE_H

#include "src/number.h"
#include "vec2.h"

class Line
{
public:
    Line();
    Line(const Vec2 &p1, const Vec2 &p2);

    Vec2 getP1() const;
    void setP1(const Vec2 &value);

    Vec2 getP2() const;
    void setP2(const Vec2 &value);

    double length();

private:
    Vec2 p1;
    Vec2 p2;
};

#endif // LINE_H
