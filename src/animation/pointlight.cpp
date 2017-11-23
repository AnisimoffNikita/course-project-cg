#include "pointlight.h"

#include "cmath"

PointLight::PointLight(const Vec3 &position, float intensity) :
    Light(position, intensity)
{
}


float PointLight::getIntensity(const Vec3 &n, const Vec3 &p,
                               const Vec3 &c) const
{
    Vec3 d = (p - position);
    float cos = -d.dot(n) / (d.length() * n.length());
    float result = 0;

    if (cos > 0)
    {
        result += intensity * cos ;
    }

    Vec3 nn = n.normalized();
    Vec3 look = p - c;
    Vec3 r = d - nn * (d.dot(nn)) * 2;
    float cosa = -look.dot(r) / (look.length() * r.length());

    if (cosa > 0)
    {
        result += 3 * Math::Pow(cosa, 5);
    }

    result  /= (d.length());
    return result;
}
