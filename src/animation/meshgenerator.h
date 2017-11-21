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

private:
    static Vertex getNormal(const Vertex &v1, const Vertex &v2, const Vertex &v3,
                            const Vertex &p);
};


class MaterialGenerator
{
public:
    static Material SimpleMaterial(const Color &color);
};

#endif // MESHGENERATOR_H
