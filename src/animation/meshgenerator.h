#ifndef MESHGENERATOR_H
#define MESHGENERATOR_H

#include "mesh.h"

using namespace std;

class MeshGenerator
{
public:
    static Mesh Cylinder(double radius, double height, int accuracy);
    static Mesh Cube(double size);
};

#endif // MESHGENERATOR_H
