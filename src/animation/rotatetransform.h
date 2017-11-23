#ifndef ROTATETRANSFORM_H
#define ROTATETRANSFORM_H


#include "transformation.h"

class RotateXTransformation : public Transformation
{
public:
    RotateXTransformation(float angle, const Vec3 &origin);

    virtual void transform(Vec3 &vertex) const override;
protected:
    Vec3 _origin;
};

class RotateYTransformation : public Transformation
{
public:
    RotateYTransformation(float angle, const Vec3 &origin);

    virtual void transform(Vec3 &vertex) const override;
protected:
    Vec3 _origin;
};

class RotateZTransformation : public Transformation
{
public:
    RotateZTransformation(float angle, const Vec3 &origin);

    virtual void transform(Vec3 &vertex) const override;
protected:
    Vec3 _origin;
};

#endif // ROTATETRANSFORM_H
