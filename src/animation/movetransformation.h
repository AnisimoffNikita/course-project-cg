#ifndef MOVETRANSFORMATION_H
#define MOVETRANSFORMATION_H

#include "transformation.h"

class MoveTransformation : public Transformation
{
public:
    MoveTransformation(const Vec3 &delta);

    virtual void transform(Vec3 &vertex) const override;
};

#endif // MOVETRANSFORMATION_H
