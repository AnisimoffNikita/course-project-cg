#include "objloader.h"

#include <regex>
#include <algorithm>
#include <fstream>

#include "src/3rdparty/ObjLoader/objloader.h"

ObjLoader::ObjLoader(const string &filename)
    : filename(filename)
{
}

Mesh ObjLoader::Load(const string &filename)
{
    //    ifstream file(filename);
    //    if (!file.is_open())
    //    {
    //        return Mesh();
    //    }
    //    vector<Vec3> vertices;
    //    vector<Vec3> normals;
    //    vector<Triangle> triangles;
    //    regex vertexRe("v\\s+([\\d\\.\\+\\-eE]+)\\s+([\\d\\.\\+\\-eE]+)\\s+([\\d\\.\\+\\-eE]+)");
    //    regex normalRe("vn\\s+([\\d\\.\\+\\-eE]+)\\s+([\\d\\.\\+\\-eE]+)\\s+([\\d\\.\\+\\-eE]+)");
    //    regex triangleRe("f\\s+(-?\\d+)\\/(-?\\d+)?\\/(-?\\d+)?\\s+(-?\\d+)\\/(-?\\d+)?\\/(-?\\d+)?\\s+(-?\\d+)\\/(-?\\d+)?\\/(-?\\d+)?(?:\\s+(-?\\d+)\\/(-?\\d+)\\/(-?\\d+))?");
    //    regex materialRe("mtllib\\s+\\w+\\.\\w+");
    //    string line;
    //    while (getline(file, line))
    //    {
    //        smatch match;
    //        if (std::regex_search(line, match, vertexRe))
    //        {
    //            auto x = stod(match[1].str());
    //            auto y = stod(match[2].str());
    //            auto z = stod(match[3].str());
    //            vertices.push_back(Vec3(x, y, z));
    //        }
    //        else if (std::regex_search(line, match, normalRe))
    //        {
    //            auto x = stod(match[1].str());
    //            auto y = stod(match[2].str());
    //            auto z = stod(match[3].str());
    //            normals.push_back(Vec3(x, y, z));
    //        }
    //        else if (std::regex_search(line, match, triangleRe))
    //        {
    //            auto v1 = stod(match[1].str());
    //            auto n1 = stod(match[3].str());
    //            auto v2 = stod(match[4].str());
    //            auto n2 = stod(match[6].str());
    //            auto v3 = stod(match[7].str());
    //            auto n3 = stod(match[9].str());
    //            triangles.push_back(Triangle(v1, v2, v3, n1, n2, n3));
    //        }
    //        //        else if(std::regex_search(line, match, materialRe))
    //        //        {
    //        //            auto v1 = match[1].str();
    //        //            auto v2 = match[0].str();
    //        //            auto v4 = match[0].str();
    //        //        }
    //    }
    //    file.close();
    //    Mesh mesh;
    //    mesh.setVertices(vertices);
    //    mesh.setNormals(normals);
    //    mesh.setTriangles(triangles);
    //    return mesh;
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
    vector<Vertex> vertices;
    vector<Triangle> triangles;

    for (unsigned i = 0; i < omesh.Vertices.size(); i += 3)
    {
        array<int, 3> v;

        for (int32 j = 0; j < 3; j++)
        {
            objl::Vertex ov = omesh.Vertices[i + j];
            Vertex cv(Vec3(ov.Position.X, ov.Position.Y, ov.Position.Z),
                      Vec3(ov.Normal.X, ov.Normal.Y, ov.Normal.Z));
            auto it = find(begin(vertices), end(vertices), cv);

            if (it != end(vertices))
            {
                v[j] = distance(begin(vertices), it);
            }
            else
            {
                vertices.push_back(cv);
                v[j] = vertices.size() - 1;
            }
        }

        triangles.push_back(Triangle(v[0], v[1], v[2]));
    }

    Mesh mesh;
    mesh.setVertices(vertices);
    mesh.setTriangles(triangles);
    objl::Material omat = omesh.MeshMaterial;
    Color ka(omat.Ka.X * 255, omat.Ka.Y * 255, omat.Ka.Z * 255);
    Color kd(omat.Kd.X * 255, omat.Kd.Y * 255, omat.Kd.Z * 255);
    Color ks(omat.Ks.X * 255, omat.Ks.Y * 255, omat.Ks.Z * 255);
    Material material(ka, kd, ks, omat.Ns, omat.Ni, omat.d);
    mesh.setMaterial(material);
    return mesh;
}
