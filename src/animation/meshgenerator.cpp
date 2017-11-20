#include "meshgenerator.h"

#include "src/math/math.h"

Mesh MeshGenerator::CylinderCarcass(double radius, double height, int accuracy)
{
    Mesh mesh;

    double z = -height/2;

    for (int i = 0; i < accuracy; i++)
    {
        double x = radius*Math::Cos(i*2*Math::PI/accuracy);
        double y = radius*Math::Sin(i*2*Math::PI/accuracy);
        mesh.addVertex(Vertex(x, y, z));
        mesh.addEdge(Edge(i, (i+1)%accuracy));
    }
    z = height/2;
    for (int i = 0; i < accuracy; i++)
    {
        double x = radius*Math::Cos(i*2*Math::PI/accuracy);
        double y = radius*Math::Sin(i*2*Math::PI/accuracy);
        mesh.addVertex(Vertex(x, y, z));
        mesh.addEdge(Edge(i+accuracy, (i+1)%accuracy+accuracy));
    }
    for (int i = 0; i < accuracy; i++)
    {
        mesh.addEdge(Edge(i, i+accuracy));
    }

    return mesh;
}

Mesh MeshGenerator::CubeCarcass(double size)
{
    Mesh mesh;
    mesh.addVertex(Vertex(-1,-1,-2));
    mesh.addVertex(Vertex(-1, 1,-2));
    mesh.addVertex(Vertex( 1, 1,-2));
    mesh.addVertex(Vertex( 1,-1,-2));
    mesh.addVertex(Vertex(-1,-1, 2));
    mesh.addVertex(Vertex(-1, 1, 2));
    mesh.addVertex(Vertex( 1, 1, 2));
    mesh.addVertex(Vertex( 1,-1, 2));
    mesh.addEdge(Edge(0,1));
    mesh.addEdge(Edge(1,2));
    mesh.addEdge(Edge(2,3));
    mesh.addEdge(Edge(3,0));
    mesh.addEdge(Edge(4,5));
    mesh.addEdge(Edge(5,6));
    mesh.addEdge(Edge(6,7));
    mesh.addEdge(Edge(7,4));
    mesh.addEdge(Edge(0,4));
    mesh.addEdge(Edge(1,5));
    mesh.addEdge(Edge(2,6));
    mesh.addEdge(Edge(3,7));

    return mesh;
}

Mesh MeshGenerator::CylinderTriangles(double radius, double height, int accuracy)
{
    Mesh mesh;

    mesh.setMaterial(MaterialGenerator::SimpleMaterial(Color(160, 0, 0)));

    double z = -height/2;

    for (int i = 0; i < accuracy; i++)
    {
        double x = radius*Math::Cos(i*2*Math::PI/accuracy);
        double y = radius*Math::Sin(i*2*Math::PI/accuracy);
        mesh.addVertex(Vertex(x, y, z));
    }
    z = height/2;
    for (int i = 0; i < accuracy; i++)
    {
        double x = radius*Math::Cos(i*2*Math::PI/accuracy);
        double y = radius*Math::Sin(i*2*Math::PI/accuracy);
        mesh.addVertex(Vertex(x, y, z));
    }

    for (int i = 1; i < accuracy-1; i++)
    {
        mesh.addTrinagle(Triangle(0, i, i+1));
    }

    for (int i = 1; i < accuracy-1; i++)
    {
        mesh.addTrinagle(Triangle(accuracy, accuracy+i, accuracy+i+1));
    }

    for (int i = 0; i < accuracy; i++)
    {
        mesh.addTrinagle(Triangle(i, accuracy+i, accuracy+(i+1)%accuracy));
        mesh.addTrinagle(Triangle(i, (i+1)%accuracy, accuracy+(i+1)%accuracy));
    }

    return mesh;
}

Material MaterialGenerator::SimpleMaterial(const Color &color)
{
    Material mat;
    mat.setDiffuseColor(color);
    return mat;
}
