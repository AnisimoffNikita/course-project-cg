#include "math.h"

#include <cmath>

double Math::Gauss2(double sigma, int x, int y)
{
    return (1.0/(2*PI*sigma*sigma))*exp(-(x*x+y*y)/(2*sigma*sigma));
}

double Math::toRadians(double degrees)
{
    return PI*degrees/180.0;
}

double Math::toDegrees(double radians)
{
    return 180.0*radians/PI;
}


