#ifndef MESHDATA_H
#define MESHDATA_H

#include "src/image/color.h"

class Edge
{
private:
    int v[2];
public:
    Edge(int v1, int v2);

    int v1() const;
    int v2() const;
};

class Triangle
{
private:
    int v[3];
    int n0;
public:
    Triangle(int v1, int v2, int v3, int n);

    int v1() const;
    int v2() const;
    int v3() const;

    int n() const;
};

class Material
{
public:
    Color getDiffuseColor() const;
    void setDiffuseColor(const Color &value);

private:
    Color diffuseColor;
};


#endif // MESHDATA_H
