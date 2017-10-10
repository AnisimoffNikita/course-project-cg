#ifndef MATH_H
#define MATH_H

#include "src/number.h"

class Math
{
public:
    constexpr static double PI = 3.14159265358979323846;

    static double Gauss2(double sigma, int x, int y);

    template<class T>
    static T Clamp(const T &value, const T &max, const T &min);

    static double toRadians(double degrees);
    static double toDegrees(double radians);

    template <typename T>
    static int32 sgn(const T &val);
};

template<class T>
T Math::Clamp(const T &value, const T &min, const T &max)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

template <typename T>
int32 Math::sgn(const T &val)
{
    return (T(0) < val) - (val < T(0));
}

#endif // MATH_H
