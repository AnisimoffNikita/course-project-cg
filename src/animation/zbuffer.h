#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <vector>
#include "src/number.h"

using namespace std;

class ZBuffer
{
public:
    ZBuffer();

    void setSize(int32 w, int32 h);
    void init();

    float get(int32 x, int32 y);
    void set(int32 x, int32 y, float value);

private:
    vector<float> buffer;
    int32 width, height;
};


#endif // ZBUFFER_H
