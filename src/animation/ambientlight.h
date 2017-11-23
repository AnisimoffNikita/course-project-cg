#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "light.h"

class AmbientLight : public Light
{
public:
    AmbientLight(float intensity);

    virtual float getIntensity(const Vec3 &, const Vec3 &,
                               const Vec3 &) const override;

    virtual bool isPoint() const override;
};

#endif // AMBIENTLIGHT_H
