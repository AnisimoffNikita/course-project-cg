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
    Vertex f = (target - eye).normalized();
    Vertex s = f.cross(up).normalized();
    Vertex u = s.cross(f);

    double data[] = {s.getX(), u.getX(), -f.getX(), 0,
                     s.getY(), u.getY(), -f.getY(), 0,
                     s.getZ(), u.getZ(), -f.getZ(), 0,
                     -s.dot(eye), -u.dot(eye), -f.dot(eye), 1};

    return Mat4(data);
}

Mat4 PerspectiveMatrix::create(double fovy, double aspect, double zNear, double zFar)
{
    double tanHalfFovy = Math::Tan(fovy / 2);

    double data[] = {1.0 / (aspect * tanHalfFovy), 0, 0, 0,
                     0, 1.0 / (tanHalfFovy), 0, 0,
                     0, 0, (zFar + zNear) / (zFar - zNear), 1,
                     0, 0, -(2 * zFar * zNear) / (zFar - zNear), 0};

    return Mat4(data);
}
