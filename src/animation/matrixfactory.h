#ifndef MATRIXFACTORY_H
#define MATRIXFACTORY_H

#include "src/math/matrix.h"
#include "src/math/vec3.h"


class ModelMatrix
{
public:
    static Mat4 create(const Vec3 &vertex);
};

class ViewMatrix
{
public:
    static Mat4 create(const Vec3 &eye, const Vec3 &target, const Vec3 &up);
};

class PerspectiveMatrix
{
public:
    static Mat4 create(float fovy, float aspect, float zNear, float zFar);
};


#endif // MATRIXFACTORY_H
