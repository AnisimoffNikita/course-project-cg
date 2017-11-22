#include "mesh.h"




vector<Vertex> Mesh::getVertices() const
{
    return vertices;
}

void Mesh::setVertices(const vector<Vertex> &value)
{
    vertices = value;
}

vector<Triangle> Mesh::getTriangles() const
{
    return triangles;
}

void Mesh::setTriangles(const vector<Triangle> &value)
{
    triangles = value;
}

Material Mesh::getMaterial() const
{
    return material;
}

void Mesh::setMaterial(const Material &value)
{
    material = value;
}

void Mesh::transform(const Transformation &transformation)
{
    for (auto &vertex : vertices)
    {
        vertex.transform(transformation);
    }
}
