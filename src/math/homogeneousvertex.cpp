#include "homogeneousvertex.h"



Vertex HomogeneousVertexConverter::ToVertex(const HomogeneousVertex &hvec)
{
    return Vertex(hvec(0,0)/hvec(3,0), hvec(1,0)/hvec(3,0), hvec(2,0)/hvec(3,0));
}

HomogeneousVertex HomogeneousVertexConverter::FromVertex(const Vertex &vec)
{
    double values[] = {vec.getX(), vec.getY(), vec.getZ(), 1.0};
    return HomogeneousVertex(values);
}
