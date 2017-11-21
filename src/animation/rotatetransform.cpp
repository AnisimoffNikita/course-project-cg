#include "rotatetransform.h"

#include "src/math/math.h"
#include "src/math/homogeneousvertex.h"

RotateXTransformation::RotateXTransformation(double angle, const Vertex &origin)
{
    double data[16] = {1, 0, 0, 0,
                       0, Math::Cos(angle), Math::Sin(angle), 0,
                       0, -Math::Sin(angle), Math::Cos(angle), 0,
                       0, 0, 0, 1
                      };
    _matrix = Mat4(data);
    _origin = origin;
}


void RotateXTransformation::transform(Vertex &vertex) const
{
    vertex -= _origin;
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix * hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
    vertex += _origin;
}

RotateYTransformation::RotateYTransformation(double angle, const Vertex &origin)
{
    double data[16] = {Math::Cos(angle), 0, -Math::Sin(angle), 0,
                       0, 1, 0, 0,
                       Math::Sin(angle), 0, Math::Cos(angle), 0,
                       0, 0, 0, 1
                      };
    _matrix = Mat4(data);
    _origin = origin;
}


void RotateYTransformation::transform(Vertex &vertex) const
{
    vertex -= _origin;
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix * hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
    vertex += _origin;
}

RotateZTransformation::RotateZTransformation(double angle, const Vertex &origin)
{
    double data[16] = {Math::Cos(angle), Math::Sin(angle), 0, 0,
                       -Math::Sin(angle), Math::Cos(angle), 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1
                      };
    _matrix = Mat4(data);
    _origin = origin;
}


void RotateZTransformation::transform(Vertex &vertex) const
{
    vertex -= _origin;
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix * hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
    vertex += _origin;
}
