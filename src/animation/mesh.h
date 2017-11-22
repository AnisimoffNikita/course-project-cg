#ifndef MESH_H
#define MESH_H

#include <vector>

#include "src/math/vec3.h"
#include "src/math/matrix.h"
#include "src/animation/transformation.h"
#include "meshdata.h"

class Edge;
class Triangle;
class Material;

class Mesh
{
private:
    std::vector<Vec3> vertices;
    std::vector<Edge> edges;
    std::vector<Vec3> normals;
    std::vector<Triangle> triangles;

    Material material;
public:
    Mesh() = default;

    void addVertex(const Vec3 &vertex);
    Vec3 getVertex(int i);
    void addEdge(const Edge &edge);
    void addTrinagle(const Triangle &triangle);


    Material getMaterial() const;
    void setMaterial(const Material &value);

    void transform(const Transformation &transformation);

    const std::vector<Triangle> &getTriangles() const;
    void setTriangles(const std::vector<Triangle> &value);

    std::vector<Vec3> getVertices() const;
    void setVertices(const std::vector<Vec3> &value);

    const std::vector<Edge> &getEdges() const;
    void setEdges(const std::vector<Edge> &value);

    const std::vector<Vec3> &getNormals() const;
    void setNormals(const std::vector<Vec3> &value);
};


#endif // MESH_H
