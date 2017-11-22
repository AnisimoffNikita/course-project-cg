#include "commontransformation.h"


CommonTransformation::CommonTransformation(const Mat4 &matrix)
{
    _matrix = matrix;
}

void CommonTransformation::transform(Vec3 &vertex) const
{
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix * hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
}


