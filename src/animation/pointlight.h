#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

class PointLight : public Light
{
public:
    PointLight(const Vec3 &position, float intensity);
    virtual ~PointLight() = default;

    virtual Color getIntensity(const Vec3 &n, const Vec3 &p,
                               const Vec3 &c, const Color &ka,
                               const Color &kd, const Color &ks, float ns) const override;


    virtual bool isPoint() const override;
};

#endif // POINTLIGHT_H
