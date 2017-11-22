#include "ambientlight.h"

AmbientLight::AmbientLight(double intensity) :
    Light(Vec3(0, 0, 0), intensity)
{
}


double AmbientLight::getIntensity(const Vec3 &) const
{
    return intensity;
}
