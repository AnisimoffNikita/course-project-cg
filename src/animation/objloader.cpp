#include "objloader.h"

#include <regex>
#include <algorithm>
#include <fstream>

#include "src/3rdparty/ObjLoader/objloader.h"
#include "meshgenerator.h"

ObjLoader::ObjLoader(const string &filename)
    : filename(filename)
{
}

Mesh ObjLoader::Load(const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return Mesh();
    }

    vector<Vec3> vertices;
    vector<Vec3> normals;
    vector<Triangle> triangles;
    regex vertexRe("v\\s+([\\d\\.\\+\\-eE]+)\\s+([\\d\\.\\+\\-eE]+)\\s+([\\d\\.\\+\\-eE]+)");
    regex normalRe("vn\\s+([\\d\\.\\+\\-eE]+)\\s+([\\d\\.\\+\\-eE]+)\\s+([\\d\\.\\+\\-eE]+)");
    regex triangleRe("f\\s+(-?\\d+)\\/(-?\\d+)?\\/(-?\\d+)?\\s+(-?\\d+)\\/(-?\\d+)?\\/(-?\\d+)?\\s+(-?\\d+)\\/(-?\\d+)?\\/(-?\\d+)?(?:\\s+(-?\\d+)\\/(-?\\d+)\\/(-?\\d+))?");
    regex materialRe("mtllib\\s+\\w+\\.\\w+");
    string line;

    while (getline(file, line))
    {
        smatch match;

        if (std::regex_search(line, match, vertexRe))
        {
            auto x = stod(match[1].str());
            auto y = stod(match[2].str());
            auto z = stod(match[3].str());
            vertices.push_back(Vec3(x, y, z));
        }
        else if (std::regex_search(line, match, normalRe))
        {
            auto x = stod(match[1].str());
            auto y = stod(match[2].str());
            auto z = stod(match[3].str());
            normals.push_back(Vec3(x, y, z));
        }
        else if (std::regex_search(line, match, triangleRe))
        {
            auto v1 = stod(match[1].str());
            auto n1 = stod(match[3].str());
            auto v2 = stod(match[4].str());
            auto n2 = stod(match[6].str());
            auto v3 = stod(match[7].str());
            auto n3 = stod(match[9].str());
            triangles.push_back(Triangle(v1, v2, v3, n1, n2, n3));
        }

        //        else if(std::regex_search(line, match, materialRe))
        //        {
        //            auto v1 = match[1].str();
        //            auto v2 = match[0].str();
        //            auto v4 = match[0].str();
        //        }
    }

    file.close();
    Mesh mesh;
    mesh.setVertices(vertices);
    mesh.setNormals(normals);
    mesh.setTriangles(triangles);
    return mesh;
}

Mesh ObjLoader::load()
{
    objl::Loader loader;
    bool loadout = loader.LoadFile(filename);

    if (!loadout)
    {
        return Mesh();
    }

    objl::Mesh omesh = loader.LoadedMeshes[0];
    vector<Vec3> vertices;
    vector<Vec3> normals;
    vector<Triangle> triangles;

    for (int i = 0; i < omesh.Vertices.size(); i += 3)
    {
        int vt[3], nt[3];

        for (int j = 0; j < 3; j++)
        {
            objl::Vertex ov = omesh.Vertices[i + j];
            Vec3 v(ov.Position.X, ov.Position.Y, ov.Position.Z);
            auto itv = find(begin(vertices), end(vertices), v);

            if (itv != end(vertices))
            {
                vt[j] = distance(begin(vertices), itv);
            }
            else
            {
                vertices.push_back(v);
                vt[j] = vertices.size() - 1;
            }

            Vec3 n(ov.Normal.X, ov.Normal.Y, ov.Normal.Z);
            auto itn = find(begin(normals), end(normals), n);

            if (itn != end(normals))
            {
                nt[j] = distance(begin(normals), itn);
            }
            else
            {
                normals.push_back(n);
                nt[j] = normals.size() - 1;
            }
        }

        triangles.push_back(Triangle(vt[0], vt[1], vt[2], nt[0], nt[1], nt[2]));
    }

    Mesh mesh;
    mesh.setNormals(normals);
    mesh.setVertices(vertices);
    mesh.setTriangles(triangles);
    objl::Material omat = omesh.MeshMaterial;
    Material mat;
    mat.setDiffuseColor(Color(omat.Kd.X * 255, omat.Kd.Y * 255, omat.Kd.Z * 255));
    mesh.setMaterial(mat);
    return mesh;
}
