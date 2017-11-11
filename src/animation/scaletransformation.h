#ifndef SCALETRANSFORMATION_H
#define SCALETRANSFORMATION_H

#include "transformation.h"

class ScaleTransformation : public Transformation
{
public:
    ScaleTransformation(const Vertex &scale, const Vertex &origin);

    virtual void transform(Vertex &vertex) override;
protected:
    Vertex _origin;
};

#endif // SCALETRANSFORMATION_H
