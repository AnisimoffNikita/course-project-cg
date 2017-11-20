#include "homogeneousvertex.h"



Vertex HomogeneousVertexConverter::ToVertex(const HomogeneousVertex &hvec)
{
//    return Vertex(hvec(0,0)/hvec(0,3), hvec(0,1)/hvec(0,3), hvec(0,2)/hvec(0,3));
    return Vertex(hvec(0,0)/hvec(3,0), hvec(1,0)/hvec(3,0), hvec(2,0)/hvec(3,0));
//    return Vertex(hvec(0,0), hvec(1,0), hvec(2,0));
}

HomogeneousVertex HomogeneousVertexConverter::FromVertex(const Vertex &vec)
{
    double values[] = {vec.x(), vec.y(), vec.z(), 1.0};
    return HomogeneousVertex(values);
}
