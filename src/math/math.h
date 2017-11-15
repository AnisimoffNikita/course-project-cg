#ifndef MATH_H
#define MATH_H

#include "src/number.h"

#include <functional>

class Math
{
public:
    using Func = std::function<double(double)>;
public:

    constexpr static double PI = 3.14159265358979323846;

    static double Gauss2(double sigma, int x, int y);

    template<class T>
    static T Clamp(const T &value, const T &max, const T &min);

    static double ToRadians(double degrees);
    static double ToDegrees(double radians);

    template <typename T>
    static int32 sgn(const T &val);

    static double Cos(double angle);
    static double Sin(double angle);
    static double Tan(double angle);
    static double Sqrt(double value);
    static double Atan(double value);

    static double Bisection(double a, double b, const Func &f, double eps = 1e-6);
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
