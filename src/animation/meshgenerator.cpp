#include "meshgenerator.h"

#include "src/math/math.h"

#include <algorithm>

Mesh MeshGenerator::CylinderCarcass(double radius, double height, int accuracy)
{
    Mesh mesh;
    double z = -height / 2;

    for (int i = 0; i < accuracy; i++)
    {
        double x = radius * Math::Cos(i * 2 * Math::PI / accuracy);
        double y = radius * Math::Sin(i * 2 * Math::PI / accuracy);
        mesh.addVertex(Vec3(x, y, z));
        mesh.addEdge(Edge(i, (i + 1) % accuracy));
    }

    z = height / 2;

    for (int i = 0; i < accuracy; i++)
    {
        double x = radius * Math::Cos(i * 2 * Math::PI / accuracy);
        double y = radius * Math::Sin(i * 2 * Math::PI / accuracy);
        mesh.addVertex(Vec3(x, y, z));
        mesh.addEdge(Edge(i + accuracy, (i + 1) % accuracy + accuracy));
    }

    for (int i = 0; i < accuracy; i++)
    {
        mesh.addEdge(Edge(i, i + accuracy));
    }

    return mesh;
}



Mesh MeshGenerator::CubeCarcass(double size)
{
    Mesh mesh;
    mesh.addVertex(Vec3(-1, -1, -2));
    mesh.addVertex(Vec3(-1, 1, -2));
    mesh.addVertex(Vec3(1, 1, -2));
    mesh.addVertex(Vec3(1, -1, -2));
    mesh.addVertex(Vec3(-1, -1, 2));
    mesh.addVertex(Vec3(-1, 1, 2));
    mesh.addVertex(Vec3(1, 1, 2));
    mesh.addVertex(Vec3(1, -1, 2));
    mesh.addEdge(Edge(0, 1));
    mesh.addEdge(Edge(1, 2));
    mesh.addEdge(Edge(2, 3));
    mesh.addEdge(Edge(3, 0));
    mesh.addEdge(Edge(4, 5));
    mesh.addEdge(Edge(5, 6));
    mesh.addEdge(Edge(6, 7));
    mesh.addEdge(Edge(7, 4));
    mesh.addEdge(Edge(0, 4));
    mesh.addEdge(Edge(1, 5));
    mesh.addEdge(Edge(2, 6));
    mesh.addEdge(Edge(3, 7));
    return mesh;
}

Mesh MeshGenerator::CylinderTriangles(double radius, double height,
                                      int accuracy)
{
    Mesh mesh;
    mesh.setMaterial(MaterialGenerator::SimpleMaterial(Color(160, 0, 0)));
    double z = -height / 2;

    for (int i = 0; i < accuracy; i++)
    {
        double x = radius * Math::Cos(i * 2 * Math::PI / accuracy);
        double y = radius * Math::Sin(i * 2 * Math::PI / accuracy);
        mesh.addVertex(Vec3(x, y, z));
    }

    z = height / 2;

    for (int i = 0; i < accuracy; i++)
    {
        double x = radius * Math::Cos(i * 2 * Math::PI / accuracy);
        double y = radius * Math::Sin(i * 2 * Math::PI / accuracy);
        mesh.addVertex(Vec3(x, y, z));
    }

    vector<Vec3> normals;
    Vec3 p(0, 0, 0);
    {
        Vec3 n = getNormal(mesh.getVertex(0), mesh.getVertex(1), mesh.getVertex(2),
                             p);
        int ni;
        normals.push_back(n);
        ni = normals.size() - 1;

        for (int i = 1; i < accuracy - 1; i++)
        {
            mesh.addTrinagle(Triangle(0, i, i + 1, ni));
        }
    }
    {
        Vec3 n = getNormal(mesh.getVertex(accuracy), mesh.getVertex(accuracy + 1),
                             mesh.getVertex(accuracy + 2), p);
        int ni;
        normals.push_back(n);
        ni = normals.size() - 1;

        for (int i = 1; i < accuracy - 1; i++)
        {
            mesh.addTrinagle(Triangle(accuracy, accuracy + i, accuracy + i + 1, ni));
        }
    }

    for (int i = 0; i < accuracy; i++)
    {
        Vec3 n = getNormal(mesh.getVertex(i), mesh.getVertex(accuracy + i),
                             mesh.getVertex(accuracy + (i + 1) % accuracy),
                             p)
                   .normalized();
        auto it = find(begin(normals), end(normals), n);
        int ni;

        if (it == end(normals))
        {
            normals.push_back(n);
            ni = normals.size() - 1;
        }
        else
        {
            ni = distance(begin(normals), it);
        }

        mesh.addTrinagle(Triangle(i, accuracy + i, accuracy + (i + 1) % accuracy, ni));
        mesh.addTrinagle(Triangle(i, (i + 1) % accuracy, accuracy + (i + 1) % accuracy,
                                  ni));
    }

    mesh.setNormals(normals);
    return mesh;
}


Vec3 MeshGenerator::getNormal(const Vec3 &v1, const Vec3 &v2,
                                const Vec3 &v3, const Vec3 &p)
{
    Vec3 u = v2 - v1;
    Vec3 v = v3 - v1;
    Vec3 n = u.cross(v).normalized();

    if (n.dot(v1) < 0)
    {
        n = -n;
    }

    return n;
}

Material MaterialGenerator::SimpleMaterial(const Color &color)
{
    Material mat;
    mat.setDiffuseColor(color);
    return mat;
}
