#include "meshgenerator.h"

#include "src/math/math.h"

Mesh MeshGenerator::Cylinder(double radius, double height, int accuracy)
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


        mesh.addEdge(Edge(i, i+accuracy));
    }

    return mesh;
}

Mesh MeshGenerator::Cube(double size)
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
