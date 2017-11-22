#ifndef ROTATETRANSFORM_H
#define ROTATETRANSFORM_H


#include "transformation.h"

class RotateXTransformation : public Transformation
{
public:
    RotateXTransformation(double angle, const Vec3 &origin);

    virtual void transform(Vec3 &vertex) const override;
protected:
    Vec3 _origin;
};

class RotateYTransformation : public Transformation
{
public:
    RotateYTransformation(double angle, const Vec3 &origin);

    virtual void transform(Vec3 &vertex) const override;
protected:
    Vec3 _origin;
};

class RotateZTransformation : public Transformation
{
public:
    RotateZTransformation(double angle, const Vec3 &origin);

    virtual void transform(Vec3 &vertex) const override;
protected:
    Vec3 _origin;
};

#endif // ROTATETRANSFORM_H
