#ifndef MESHGENERATOR_H
#define MESHGENERATOR_H

#include "mesh.h"

using namespace std;

class MeshGenerator
{
public:
    static Mesh CylinderCarcass(double radius, double height, int accuracy);
    static Mesh CubeCarcass(double size);

    static Mesh CylinderTriangles(double radius, double height, int accuracy);
};

class MaterialGenerator
{
public:
    static Material SimpleMaterial(const Color &color);
};

#endif // MESHGENERATOR_H
