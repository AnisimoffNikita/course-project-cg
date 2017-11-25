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

    unsigned get(int x, int y);
    void set(int x, int y, unsigned value);

private:
    vector<unsigned> buffer;
    int width, height;
};


#endif // ZBUFFER_H
