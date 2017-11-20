#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <vector>

using namespace std;

class ZBuffer
{
public:
    ZBuffer();

    void setSize(int w, int h);
    void init();

    int get(int i, int j);
    void set(int i, int j, int value);

private:
    vector<vector<int>> buffer;
    int width, height;
};


#endif // ZBUFFER_H
