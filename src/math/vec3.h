#ifndef VEC3_H
#define VEC3_H

#include "src/number.h"
#include "math.h"

template <class T>
class Vec3
{
public:
    Vec3() : x(0), y(0), z(0) {}
    Vec3(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {}

    T getX() const
    {
        return x;
    }

    void setX(const T &value)
    {
        x = value;
    }

    T getY() const
    {
        return y;
    }

    void setY(const T &value)
    {
        y = value;
    }

    T getZ() const
    {
        return z;
    }

    void setZ(const T &value)
    {
        z = value;
    }

    Vec3 &operator+= (const Vec3 &value)
    {
        x += value.x;
        y += value.y;
        z += value.z;
        return *this;
    }
    Vec3 &operator-= (const Vec3 &value)
    {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        return *this;
    }
    Vec3 &operator*= (double factor)
    {
        x *= factor;
        y *= factor;
        z *= factor;
        return *this;
    }

    Vec3 operator+ (const Vec3 &value) const
    {
        return Vec3(x+value.x, y+value.y, z+value.z);
    }

    Vec3 operator- (const Vec3 &value) const
    {
        return Vec3(x-value.x, y-value.y, z-value.z);
    }

    Vec3 operator*(double factor) const
    {
        return Vec3(x*factor,y*factor,z*factor);
    }


    Vec3 operator- () const
    {
        return Vec3(-x,-y,-z);
    }

    Vec3 normalized() const
    {
        double l = Math::Sqrt(x*x+y*y+z*z);
        return Vec3(x/l, y/l, z/l);
    }

    T dot(const Vec3 &value) const
    {
        return x*value.x + y*value.y + z*value.z;
    }

    Vec3 cross(const Vec3 &value) const
    {
        return Vec3(y*value.z-z*value.y,
                    -x*value.z+z*value.x,
                    x*value.y-y*value.x);
    }

private:
    T x;
    T y;
    T z;
};

using Vertex = Vec3<double>;

#endif // VEC3_H
