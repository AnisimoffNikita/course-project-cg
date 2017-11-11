#ifndef MATRIXFACTORY_H
#define MATRIXFACTORY_H

#include "src/math/matrix.h"
#include "src/math/vec3.h"


class ModelMatrix
{
public:
    static Mat4 create(const Vertex &vertex);
};

class ViewMatrix
{
public:
    static Mat4 create(const Vertex &eye, const Vertex &target, const Vertex &up);
};

class PerspectiveMatrix
{
public:
    static Mat4 create(double fovy, double aspect, double zNear, double zFar);
};


#endif // MATRIXFACTORY_H
