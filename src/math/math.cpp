#include "math.h"

#include <cmath>

double Math::Gauss2(double sigma, int32 x, int32 y)
{
    return (1.0 / (2 * PI * sigma * sigma)) * exp(-(x * x + y * y) /
            (2 * sigma * sigma));
}

double Math::ToRadians(double degrees)
{
    return PI * degrees / 180.0;
}

double Math::ToDegrees(double radians)
{
    return 180.0 * radians / PI;
}

double Math::Cos(double angle)
{
    return cos(angle);
}

double Math::Sin(double angle)
{
    return sin(angle);
}

double Math::Tan(double angle)
{
    return tan(angle);
}

double Math::Sqrt(double value)
{
    return sqrt(value);
}

double Math::Atan(double value)
{
    return atan(value);
}

double Math::Abs(double value)
{
    return abs(value);
}

double Math::Pow(double x, double y)
{
    return pow(x, y);
}

double Math::Ctg(double x)
{
    return cos(x) / sin(x);
}

double Math::Bisection(double a, double b, const Func &f, double eps)
{
    double x = (a + b) * 0.5;
    float check = f(x) * f(a);

    if (check != 0)
    {
        while (fabs(b - a) > eps * fabs(x) + eps)
        {
            if (check < 0)
            {
                b = x;
            }
            else
            {
                a = x;
            }

            x = (a + b) * 0.5;
            check = f(x) * f(a);
        }

        return x;
    }
    else
    {
        if (f(x) == 0)
        {
            return x;
        }
        else
        {
            return a;
        }
    }
}
