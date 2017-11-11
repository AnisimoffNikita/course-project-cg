#ifndef VEC2_H
#define VEC2_H

#include "src/number.h"

template <class T>
class Vec2
{
public:
    Vec2() : x(0), y(0) {}
    Vec2(const T& x, const T& y) : x(x), y(y) {}

    T getX() const
    {
        return x;
    }

    void setX(const T &value)
    {
        x = value;
    }

    T getY() const
    {
        return y;
    }

    void setY(const T &value)
    {
        y = value;
    }

private:
    T x;
    T y;
};

using Point = Vec2<int32>;

#endif // VEC2_H
