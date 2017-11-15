#include "movetransformation.h"

#include "src/math/homogeneousvertex.h"

MoveTransformation::MoveTransformation(const Vertex &delta)
{
    double data[16] = {1, 0, 0, delta.getX(),
                       0, 1, 0, delta.getY(),
                       0, 0, 1, delta.getZ(),
                       0, 0, 0, 1};
    _matrix = Mat4(data);
}


void MoveTransformation::transform(Vertex &vertex) const
{
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix*hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
}
