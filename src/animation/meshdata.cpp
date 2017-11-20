#include "meshdata.h"


Edge::Edge(int v1, int v2) :
    v{v1,v2}
{}

int Edge::v1() const
{
    return v[0];
}

int Edge::v2() const
{
    return v[1];
}


Triangle::Triangle(int v1, int v2, int v3, int n) :
    v{v1,v2,v3},
    n0(n)
{

}

int Triangle::v1() const
{
    return v[0];
}

int Triangle::v2() const
{
    return v[1];
}

int Triangle::v3() const
{
    return v[2];
}

int Triangle::n() const
{
    return n0;
}

Color Material::getDiffuseColor() const
{
    return diffuseColor;
}

void Material::setDiffuseColor(const Color &value)
{
    diffuseColor = value;
}
