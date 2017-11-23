#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

class PointLight : public Light
{
public:
    PointLight(const Vec3 &position, float intensity);
    virtual ~PointLight() = default;

    virtual float getIntensity(const Vec3 &n, const Vec3 &p,
                               const Vec3 &c) const override;


    virtual bool isPoint() const override;
};

#endif // POINTLIGHT_H
