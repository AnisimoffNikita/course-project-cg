#ifndef VEC3_H
#define VEC3_H

#include "src/number.h"
#include "math.h"

template <class T>
class Vector3
{
public:
    Vector3() : xc(0), yc(0), zc(0) {}
    Vector3(const T &x, const T &y, const T &z) : xc(x), yc(y), zc(z) {}

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

    Vector3 &operator+= (const Vector3 &value)
    {
        xc += value.xc;
        yc += value.yc;
        zc += value.zc;
        return *this;
    }
    Vector3 &operator-= (const Vector3 &value)
    {
        xc -= value.xc;
        yc -= value.yc;
        zc -= value.zc;
        return *this;
    }
    Vector3 &operator*= (double factor)
    {
        xc *= factor;
        yc *= factor;
        zc *= factor;
        return *this;
    }

    Vector3 operator+ (const Vector3 &value) const
    {
        return Vector3(xc + value.xc, yc + value.yc, zc + value.zc);
    }

    Vector3 operator- (const Vector3 &value) const
    {
        return Vector3(xc - value.xc, yc - value.yc, zc - value.zc);
    }

    Vector3 operator*(double factor) const
    {
        return Vector3(xc * factor, yc * factor, zc * factor);
    }

    bool operator==(const Vector3 &value) const
    {
        return xc == value.xc &&
               yc == value.yc &&
               zc == value.zc;
    }


    Vector3 operator- () const
    {
        return Vector3(-xc, -yc, -zc);
    }

    Vector3 normalized() const
    {
        double l = Math::Sqrt(xc * xc + yc * yc + zc * zc);
        return Vector3(xc / l, yc / l, zc / l);
    }

    T dot(const Vector3 &value) const
    {
        return xc * value.xc + yc * value.yc + zc * value.zc;
    }

    Vector3 cross(const Vector3 &value) const
    {
        return Vector3(yc * value.zc - zc * value.yc,
                       -xc * value.zc + zc * value.xc,
                       xc * value.yc - yc * value.xc);
    }

private:
    T xc;
    T yc;
    T zc;
};

using Vec3 = Vector3<double>;

#endif // VEC3_H
