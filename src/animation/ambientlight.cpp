#include "ambientlight.h"

AmbientLight::AmbientLight(double intensity) :
    Light(Vertex(0, 0, 0), intensity)
{
}


double AmbientLight::getIntensity(const Vertex &) const
{
    return intensity;
}
