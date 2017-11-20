#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

class PointLight : public Light
{
public:
    PointLight(const Vertex &position, double intensity);

    virtual double getIntensity(const Vertex &normal) const override;

protected:
    double intensity;
};

#endif // POINTLIGHT_H
