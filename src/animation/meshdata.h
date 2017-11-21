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
    int n[3];
public:
    Triangle(int v1, int v2, int v3, int n1 = -1, int n2 = -1, int n3 = -1);

    int v1() const;
    void setV1(int value);
    int v2() const;
    void setV2(int value);
    int v3() const;
    void setV3(int value);

    int n1() const;
    void setN1(int value);
    int n2() const;
    void setN2(int value);
    int n3() const;
    void setN3(int value);
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
