#include "scaletransformation.h"

#include "src/math/homogeneousvertex.h"

ScaleTransformation::ScaleTransformation(const Vec3 &scale,
        const Vec3 &origin)
{
    double data[16] = {scale.x(), 0, 0, 0,
                       0, scale.y(), 0, 0,
                       0, 0, scale.z(), 0,
                       0, 0, 0, 1
                      };
    _matrix = Mat4(data);
    _origin = origin;
}


void ScaleTransformation::transform(Vec3 &vertex) const
{
    vertex -= _origin;
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix * hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
    vertex += _origin;
}
