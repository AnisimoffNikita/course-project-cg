#include "mesh.h"

Mesh::Mesh()
{

}


Edge::Edge(int v1, int v2) :
    _v1(v1), _v2(v2)
{}

int Edge::v1() const
{
    return _v1;
}

int Edge::v2() const
{
    return _v2;
}
