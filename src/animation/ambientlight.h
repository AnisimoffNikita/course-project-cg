#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "light.h"

class AmbientLight : public Light
{
public:
    AmbientLight(double intensity);

    virtual double getIntensity(const Vec3 &) const override;
};

#endif // AMBIENTLIGHT_H
