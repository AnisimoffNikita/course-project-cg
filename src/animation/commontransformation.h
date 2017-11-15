#ifndef COMMONTRANSFORMATION_H
#define COMMONTRANSFORMATION_H

#include "transformation.h"
#include "src/math/homogeneousvertex.h"

class CommonTransformation : public Transformation
{
public:
    CommonTransformation(const Mat4 &matrix);

    virtual void transform(Vertex &vertex) const override;
};

#endif // COMMONTRANSFORMATION_H
