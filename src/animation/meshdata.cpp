#include "meshdata.h"

Edge::Edge(int v1, int v2)
    : v{ v1, v2 }
{
}

int Edge::v1() const
{
    return v[0];
}

int Edge::v2() const
{
    return v[1];
}

Triangle::Triangle(int v1, int v2, int v3, int n1, int n2, int n3)
    : v{ v1, v2, v3 }
    , n{ n1, n2, n3 }
{
}

int Triangle::v1() const
{
    return v[0];
}

void Triangle::setV1(int value)
{
    v[0] = value;
}

int Triangle::v2() const
{
    return v[1];
}

void Triangle::setV2(int value)
{
    v[1] = value;
}

int Triangle::v3() const
{
    return v[2];
}

void Triangle::setV3(int value)
{
    v[2] = value;
}

int Triangle::n1() const
{
    return n[0];
}

void Triangle::setN1(int value)
{
    n[0] = value;
}

int Triangle::n2() const
{
    return n[1];
}

void Triangle::setN2(int value)
{
    n[1] = value;
}

int Triangle::n3() const
{
    return n[2];
}

void Triangle::setN3(int value)
{
    n[2] = value;
}
Color Material::getDiffuseColor() const
{
    return diffuseColor;
}

void Material::setDiffuseColor(const Color &value)
{
    diffuseColor = value;
}
