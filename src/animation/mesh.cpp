#include "mesh.h"



void Mesh::addVertex(const Vertex &vertex)
{
    vertices.push_back(vertex);
}

void Mesh::addEdge(const Edge &edge)
{
    edges.push_back(edge);
}

const std::vector<Vertex> &Mesh::getVertices() const
{
    return vertices;
}

const std::vector<Edge> &Mesh::getEdges() const
{
    return edges;
}

void Mesh::transform(const Transformation &transformation)
{
    for (auto &vertex : vertices)
        transformation.transform(vertex);
}


Edge::Edge(int v1, int v2) :
    v{v1,v2}
{}

int Edge::v1() const
{
    return v[0];
}

int Edge::v2() const
{
    return v[1];
}


Triangle::Triangle(int v1, int v2, int v3) :
    v{v1,v2,v3}
{

}

int Triangle::v1() const
{
    return v[0];
}

int Triangle::v2() const
{
    return v[1];
}

int Triangle::v3() const
{
    return v[2];
}
