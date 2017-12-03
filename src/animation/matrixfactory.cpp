#include "matrixfactory.h"


Mat4 ModelMatrix::create(const Vec3 &vertex)
{
    float data[16] = {1, 0, 0, vertex.x(),
                      0, 1, 0, vertex.y(),
                      0, 0, 1, vertex.z(),
                      0, 0, 0, 1
                     };
    return Mat4(data);
}

Mat4 ViewMatrix::create(const Vec3 &eye, const Vec3 &target,
                        const Vec3 &up)
{
    Vec3 z = (target - eye).normalized();
    Vec3 x = -z.cross(up).normalized();
    Vec3 y = -x.cross(z);
    float data[] = {x.x(), x.y(), x.z(), -x.dot(eye),
                    y.x(), y.y(), y.z(), -y.dot(eye),
                    z.x(), z.y(), z.z(), -z.dot(eye),
                    0, 0, 0, 1
                   };
    return Mat4(data);
}

Mat4 PerspectiveMatrix::create(float fovx, float fovy, float zNear,
                               float zFar)
{
    float data[] = {(float)Math::Atan(fovx / 2), 0, 0, 0,
                    0, (float)Math::Atan(fovy / 2), 0, 0,
                    0, 0, (zFar + zNear) / (zFar - zNear), -(2 * zFar * zNear) / (zFar - zNear),
                    0, 0, 1, 0
                   };
    return Mat4(data);
}
