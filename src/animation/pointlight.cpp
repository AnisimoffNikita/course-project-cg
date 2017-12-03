#include "pointlight.h"

#include "cmath"

PointLight::PointLight(const Vec3 &position, float intensity) :
    Light(position, intensity)
{
}


Color PointLight::getIntensity(const Vec3 &n, const Vec3 &p,
                               const Vec3 &c,
                               const Color &ka, const Color &kd, const Color &ks, float ns) const
{
    Vec3 d = (p - position);
    float cos = -d.dot(n) / (d.length() * n.length());
    uint32 r, g, b;
    r = g = b = 0;

    if (cos > 0)
    {
        r += kd.getRed() * cos;
        g += kd.getGreen() * cos;
        b += kd.getBlue() * cos;
    }

    Vec3 nn = n.normalized();
    Vec3 look = p - c;
    Vec3 rl = d - nn * (d.dot(nn)) * 2;
    float cosa = -look.dot(rl) / (look.length() * rl.length());

    if (cosa > 0)
    {
        r += ks.getRed() * Math::Pow(cosa, ns);
        g += ks.getGreen() * Math::Pow(cosa, ns);
        b += ks.getBlue() * Math::Pow(cosa, ns);
    }

    r *= intensity / d.length();
    g *= intensity / d.length();
    b *= intensity / d.length();
    r = Math::Clamp(r, 0u, 255u);
    g = Math::Clamp(g, 0u, 255u);
    b = Math::Clamp(b, 0u, 255u);
    return Color(r, g, b);
}


bool PointLight::isPoint() const
{
    return true;
}
