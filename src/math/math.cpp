#include "math.h"

#include <cmath>

float Math::Gauss2(float sigma, int x, int y)
{
    return (1.0/(2*M_PI*sigma*sigma))*exp(-(x*x+y*y)/(2*sigma*sigma));
}
