#include "mesh.h"



void Mesh::addVertex(const Vertex &vertex)
{
    _vertices.push_back(vertex);
}

void Mesh::addEdge(const Edge &edge)
{
    _edges.push_back(edge);
}

const std::vector<Vertex> &Mesh::getVertices() const
{
    return _vertices;
}

const std::vector<Edge> &Mesh::getEdges() const
{
    return _edges;
}

void Mesh::transform(const Transformation &transformation)
{
    for (auto &vertex : _vertices)
        transformation.transform(vertex);
}


Edge::Edge(int v1, int v2) :
    _v1(v1), _v2(v2)
{}

int Edge::v1() const
{
    return _v1;
}

int Edge::v2() const
{
    return _v2;
}

