#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "src/math/vec3.h"
#include "src/math/matrix.h"

class Transformation
{
public:
    Transformation();
    virtual ~Transformation() = default;

    const Mat4 &getMatrix();

    virtual void transform(Vec3 &vertex) const = 0;

protected:
    Mat4 _matrix;
};

#endif // TRANSFORMATION_H
