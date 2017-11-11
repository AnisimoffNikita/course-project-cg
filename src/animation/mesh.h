#ifndef MESH_H
#define MESH_H

#include <vector>

#include "src/math/vec3.h"
#include "src/math/matrix.h"
#include "src/animation/transformation.h"

class Edge;

class Mesh
{
private:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
public:
    Mesh();

    void addVertex(const Vertex &vertex);
    void addEdge(const Edge &edge);

    const std::vector<Vertex> &getVertices() const;
    const std::vector<Edge> &getEdges() const;

    void transform(const Transformation &transformation);
};

class Edge
{
private:
    int _v1, _v2;
public:
    Edge(int v1, int v2);

    int v1() const;
    int v2() const;
};

#endif // MESH_H
