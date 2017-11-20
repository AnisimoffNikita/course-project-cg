#include "matrixfactory.h"


Mat4 ModelMatrix::create(const Vertex &vertex)
{
    double data[16] = {1, 0, 0, vertex.x(),
                       0, 1, 0, vertex.y(),
                       0, 0, 1, vertex.z(),
                       0, 0, 0, 1};
    return Mat4(data);
}

Mat4 ViewMatrix::create(const Vertex &eye, const Vertex &target, const Vertex &up)
{
    Vertex z = (target - eye).normalized();
    Vertex x = z.cross(up).normalized();
    Vertex y = x.cross(z);

    double data[] = {x.x(), x.y(), x.z(), -x.dot(eye),
                     y.x(), y.y(), y.z(), -y.dot(eye),
                     z.x(), z.y(), z.z(), -z.dot(eye),
                     0, 0, 0, 1};

    return Mat4(data);
}

Mat4 PerspectiveMatrix::create(double fovx, double fovy, double zNear, double zFar)
{

    double data[] = {Math::Atan(fovx / 2), 0, 0, 0,
                     0, Math::Atan(fovy / 2), 0, 0,
                     0, 0, -(zFar + zNear) / (zFar - zNear), -1,
                     0, 0, -(2 * zFar*zNear) / (zFar - zNear), 0};

    return Mat4(data);
}
