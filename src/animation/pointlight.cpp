#include "pointlight.h"

PointLight::PointLight(const Vertex &position, double intensity) :
    Light(position),
    intensity(intensity)
{
}


double PointLight::getIntensity(const Vertex &normal) const
{
    constexpr double K = 0;

    Vertex light = (normal - position);

    double cos = light.dot(normal) / (light.length()*normal.length());

    if (cos < 0)
        return 0;

    return intensity*cos / (light.length() + K);
}
