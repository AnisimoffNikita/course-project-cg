#ifndef SCALETRANSFORMATION_H
#define SCALETRANSFORMATION_H

#include "transformation.h"

class ScaleTransformation : public Transformation
{
public:
    ScaleTransformation(const Vec3 &scale, const Vec3 &setOrigin);

    virtual void transform(Vec3 &vertex) const override;
protected:
    Vec3 _origin;
};

#endif // SCALETRANSFORMATION_H
