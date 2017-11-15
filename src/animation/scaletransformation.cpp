#include "scaletransformation.h"

#include "src/math/homogeneousvertex.h"

ScaleTransformation::ScaleTransformation(const Vertex &scale, const Vertex &origin)
{
    double data[16] = {scale.getX(), 0, 0, 0,
                       0, scale.getY(), 0, 0,
                       0, 0, scale.getZ(), 0,
                       0, 0, 0, 1};
    _matrix = Mat4(data);
    _origin = origin;
}


void ScaleTransformation::transform(Vertex &vertex) const
{
    vertex -= _origin;
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix*hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
    vertex += _origin;
}
