#include "pointlight.h"

#include "cmath"

PointLight::PointLight(const Vertex &position, double intensity) :
    Light(position, intensity)
{
}


double PointLight::getIntensity(const Vertex &normal) const
{
    constexpr double K = 0;
    Vertex light = (normal - position);
    double cos = -light.dot(normal) / (light.length() * normal.length());

    if (cos < 0)
    {
        return 0;
    }

    auto result = intensity * cos / (light.length() + K);

    if (std::isnan(result))
    {
        int a;
        a = 4;
    }

    return intensity * cos / (light.length() + K);
}
