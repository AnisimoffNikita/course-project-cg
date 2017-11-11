#include "transformation.h"


Transformation::Transformation()
{
}

const Mat4 &Transformation::getMatrix()
{
    return _matrix;
}

