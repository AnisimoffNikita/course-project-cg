#include "matrixfactory.h"


Mat4 ModelMatrix::create(const Vertex &vertex)
{
    double data[16] = {1, 0, 0, vertex.getX(),
                       0, 1, 0, vertex.getY(),
                       0, 0, 1, vertex.getZ(),
                       0, 0, 0, 1};
    return Mat4(data);
}

Mat4 ViewMatrix::create(const Vertex &eye, const Vertex &target, const Vertex &up)
{
    Vertex z = (target - eye).normalized();
    Vertex x = z.cross(up).normalized();
    Vertex y = x.cross(z);

    double data[] = {x.getX(), x.getY(), x.getZ(), -x.dot(eye),
                     y.getX(), y.getY(), y.getZ(), -y.dot(eye),
                     z.getX(), z.getY(), z.getZ(), -z.dot(eye),
                     0, 0, 0, 1};

    return Mat4(data);
}

Mat4 PerspectiveMatrix::create(double fovx, double fovy, double zNear, double zFar)
{

    double data[] = {Math::Atan(fovx / 2), 0, 0, 0,
                     0, Math::Atan(fovy / 2), 0, 0,
                     0, 0, -(zFar + zNear) / (zFar - zNear), -1,
                     0, 0, -(2 * zFar*zNear) / (zFar - zNear), 0};

//    double data[] = {1, 0, 0, 0,
//                     0, 1, 0, 0,
//                     0, 0, 1, 0,
//                     0, 0, -0.1, 1};

    return Mat4(data);
}
