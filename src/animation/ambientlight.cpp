#include "ambientlight.h"

AmbientLight::AmbientLight(float intensity) :
    Light(Vec3(0, 0, 0), intensity)
{
}


Color AmbientLight::getIntensity(const Vec3 &, const Vec3 &, const Vec3 &,
                                 const Color &ka, const Color &, const Color &, float) const
{
    return ka * intensity;
}


bool AmbientLight::isPoint() const
{
    return false;
}
