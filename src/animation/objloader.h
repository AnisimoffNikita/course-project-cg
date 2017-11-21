#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "mesh.h"

#include <string>
using namespace std;


class ObjLoader
{
public:
    ObjLoader(const string &filename);

    static Mesh Load(const string &filename);

    Mesh load();
private:

    string filename;
};

#endif // OBJLOADER_H


