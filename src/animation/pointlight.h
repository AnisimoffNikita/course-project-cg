#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

class PointLight : public Light
{
public:
    PointLight(const Vec3 &position, double intensity);
    virtual ~PointLight() = default;

    virtual double getIntensity(const Vec3 &normal) const override;

};

#endif // POINTLIGHT_H
