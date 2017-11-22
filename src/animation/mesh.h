#ifndef MESH_H
#define MESH_H

#include <vector>

#include "src/math/vec3.h"
#include "src/math/matrix.h"
#include "src/animation/transformation.h"
#include "meshdata.h"

using namespace std;


class Mesh
{
public:
    Mesh() = default;

    vector<Vertex> &getVertices();
    void setVertices(const vector<Vertex> &value);

    vector<Triangle> &getTriangles();
    void setTriangles(const vector<Triangle> &value);

    Material &getMaterial();
    void setMaterial(const Material &value);

    void transform(const Transformation &transformation);

private:
    vector<Vertex> vertices;
    vector<Triangle> triangles;
    Material material;
};



#endif // MESH_H
