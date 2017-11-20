#include "mesh.h"


const std::vector<Vertex> &Mesh::getNormals() const
{
    return normals;
}

void Mesh::setNormals(const std::vector<Vertex> &value)
{
    normals = value;
}

void Mesh::addVertex(const Vertex &vertex)
{
    vertices.push_back(vertex);
}

Vertex Mesh::getVertex(int i)
{
    return vertices[i];
}

void Mesh::addEdge(const Edge &edge)
{
    edges.push_back(edge);
}

void Mesh::addTrinagle(const Triangle &triangle)
{
    triangles.push_back(triangle);
}


Material Mesh::getMaterial() const
{
    return material;
}

void Mesh::setMaterial(const Material &value)
{
    material = value;
}

const std::vector<Triangle> &Mesh::getTriangles() const
{
    return triangles;
}

void Mesh::setTriangles(const std::vector<Triangle> &value)
{
    triangles = value;
}

void Mesh::setEdges(const std::vector<Edge> &value)
{
    edges = value;
}


std::vector<Vertex> Mesh::getVertices() const
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

