#ifndef SCALETRANSFORMATION_H
#define SCALETRANSFORMATION_H

#include "transformation.h"

class ScaleTransformation : public Transformation
{
public:
    ScaleTransformation(const Vertex &scale, const Vertex &setOrigin);

    virtual void transform(Vertex &vertex) const override;
protected:
    Vertex _origin;
};

#endif // SCALETRANSFORMATION_H
