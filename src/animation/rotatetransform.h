#ifndef ROTATETRANSFORM_H
#define ROTATETRANSFORM_H


#include "transformation.h"

class RotateXTransformation : public Transformation
{
public:
    RotateXTransformation(double angle, const Vertex &origin);

    virtual void transform(Vertex &vertex) override;
protected:
    Vertex _origin;
};

class RotateYTransformation : public Transformation
{
public:
    RotateYTransformation(double angle, const Vertex &origin);

    virtual void transform(Vertex &vertex) override;
protected:
    Vertex _origin;
};

class RotateZTransformation : public Transformation
{
public:
    RotateZTransformation(double angle, const Vertex &origin);

    virtual void transform(Vertex &vertex) override;
protected:
    Vertex _origin;
};

#endif // ROTATETRANSFORM_H
