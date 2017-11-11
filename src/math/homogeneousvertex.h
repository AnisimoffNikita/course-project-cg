#ifndef HOMOGENEOUSVERTEX_H
#define HOMOGENEOUSVERTEX_H

#include "src/math/vec3.h"
#include "src/math/matrix.h"

using HomogeneousVertex = Matrix<4, 1, double>;

class HomogeneousVertexConverter
{
public:
    static Vertex ToVertex(const HomogeneousVertex &hvec);
    static HomogeneousVertex FromVertex(const Vertex &vec);
};

#endif // HOMOGENEOUSVERTEX_H
