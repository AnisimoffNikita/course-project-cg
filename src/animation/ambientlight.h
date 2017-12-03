#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "light.h"

class AmbientLight : public Light
{
public:
    AmbientLight(float intensity);

    virtual Color getIntensity(const Vec3 &, const Vec3 &,
                               const Vec3 &, const Color &ka, const Color &, const Color &,
                               float) const override;

    virtual bool isPoint() const override;
};

#endif // AMBIENTLIGHT_H
