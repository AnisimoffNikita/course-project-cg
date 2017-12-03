#include "rotatetransform.h"

#include "src/math/math.h"
#include "src/math/homogeneousvertex.h"

RotateXTransformation::RotateXTransformation(float angle, const Vec3 &origin)
{
    float data[16] = {1, 0, 0, 0,
                      0, (float)Math::Cos(angle), (float)Math::Sin(angle), 0,
                      0, (float) - Math::Sin(angle), (float)Math::Cos(angle), 0,
                      0, 0, 0, 1
                     };
    _matrix = Mat4(data);
    _origin = origin;
}


void RotateXTransformation::transform(Vec3 &vertex) const
{
    vertex -= _origin;
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix * hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
    vertex += _origin;
}

void RotateXTransformation::resetOrigin()
{
    _origin = Vec3(0, 0, 0);
}

RotateYTransformation::RotateYTransformation(float angle, const Vec3 &origin)
{
    float data[16] = {(float)Math::Cos(angle), 0, (float) - Math::Sin(angle), 0,
                      0, 1, 0, 0,
                      (float)Math::Sin(angle), 0, (float)Math::Cos(angle), 0,
                      0, 0, 0, 1
                     };
    _matrix = Mat4(data);
    _origin = origin;
}


void RotateYTransformation::transform(Vec3 &vertex) const
{
    vertex -= _origin;
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix * hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
    vertex += _origin;
}

void RotateYTransformation::resetOrigin()
{
    _origin = Vec3(0, 0, 0);
}

RotateZTransformation::RotateZTransformation(float angle, const Vec3 &origin)
{
    float data[16] = {(float)Math::Cos(angle), (float)Math::Sin(angle), 0, 0,
                      (float) - Math::Sin(angle), (float)Math::Cos(angle), 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1
                     };
    _matrix = Mat4(data);
    _origin = origin;
}


void RotateZTransformation::transform(Vec3 &vertex) const
{
    vertex -= _origin;
    HomogeneousVertex hvec = HomogeneousVertexConverter::FromVertex(vertex);
    hvec = _matrix * hvec;
    vertex = HomogeneousVertexConverter::ToVertex(hvec);
    vertex += _origin;
}

void RotateZTransformation::resetOrigin()
{
    _origin = Vec3(0, 0, 0);
}
