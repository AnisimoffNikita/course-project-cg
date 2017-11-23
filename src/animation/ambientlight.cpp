#include "ambientlight.h"

AmbientLight::AmbientLight(float intensity) :
    Light(Vec3(0, 0, 0), intensity)
{
}


float AmbientLight::getIntensity(const Vec3 &, const Vec3 &, const Vec3 &) const
{
    return intensity;
}
