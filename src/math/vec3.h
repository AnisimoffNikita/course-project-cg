#ifndef VEC3_H
#define VEC3_H

#include "src/number.h"
#include "math.h"

template <class T>
class Vec3
{
public:
    Vec3() : xc(0), yc(0), zc(0) {}
    Vec3(const T &x, const T &y, const T &z) : xc(x), yc(y), zc(z) {}

    T x() const
    {
        return xc;
    }

    void setX(const T &value)
    {
        xc = value;
    }

    T y() const
    {
        return yc;
    }

    void setY(const T &value)
    {
        yc = value;
    }

    T z() const
    {
        return zc;
    }

    void setZ(const T &value)
    {
        zc = value;
    }

    double length() const
    {
        return Math::Sqrt(xc * xc + yc * yc + zc * zc);
    }

    Vec3 &operator+= (const Vec3 &value)
    {
        xc += value.xc;
        yc += value.yc;
        zc += value.zc;
        return *this;
    }
    Vec3 &operator-= (const Vec3 &value)
    {
        xc -= value.xc;
        yc -= value.yc;
        zc -= value.zc;
        return *this;
    }
    Vec3 &operator*= (double factor)
    {
        xc *= factor;
        yc *= factor;
        zc *= factor;
        return *this;
    }

    Vec3 operator+ (const Vec3 &value) const
    {
        return Vec3(xc + value.xc, yc + value.yc, zc + value.zc);
    }

    Vec3 operator- (const Vec3 &value) const
    {
        return Vec3(xc - value.xc, yc - value.yc, zc - value.zc);
    }

    Vec3 operator*(double factor) const
    {
        return Vec3(xc * factor, yc * factor, zc * factor);
    }

    bool operator==(const Vec3 &value) const
    {
        return xc == value.xc &&
               yc == value.yc &&
               zc == value.zc;
    }


    Vec3 operator- () const
    {
        return Vec3(-xc, -yc, -zc);
    }

    Vec3 normalized() const
    {
        double l = Math::Sqrt(xc * xc + yc * yc + zc * zc);
        return Vec3(xc / l, yc / l, zc / l);
    }

    T dot(const Vec3 &value) const
    {
        return xc * value.xc + yc * value.yc + zc * value.zc;
    }

    Vec3 cross(const Vec3 &value) const
    {
        return Vec3(yc * value.zc - zc * value.yc,
                    -xc * value.zc + zc * value.xc,
                    xc * value.yc - yc * value.xc);
    }

private:
    T xc;
    T yc;
    T zc;
};

using Vertex = Vec3<double>;

#endif // VEC3_H
