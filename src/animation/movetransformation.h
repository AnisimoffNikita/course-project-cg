#ifndef MOVETRANSFORMATION_H
#define MOVETRANSFORMATION_H

#include "transformation.h"

class MoveTransformation : public Transformation
{
public:
    MoveTransformation(const Vertex &delta);

    virtual void transform(Vertex &vertex) override;
};

#endif // MOVETRANSFORMATION_H
