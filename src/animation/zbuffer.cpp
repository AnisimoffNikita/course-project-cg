#include "zbuffer.h"

#include <limits>

ZBuffer::ZBuffer()
{
}

void ZBuffer::setSize(int w, int h)
{
    width = w;
    height = h;
    buffer.resize(height * width);
}

void ZBuffer::init()
{
    unsigned min = ~0;

    for (int i = 0; i < height * width; i++)
    {
        buffer[i] = min;
    }
}

float ZBuffer::get(int x, int y)
{
    //    if (x >= 0 && x < width && y >= 0 && y < height)
    //    {
    return buffer[y * width + x];
    //    }
    //    else
    //    {
    //        return numeric_limits<int>::min();
    //    }
}

void ZBuffer::set(int x, int y, float value)
{
    //    if (x >= 0 && x < width && y >= 0 && y < height)
    //    {
    buffer[y * width + x] = value;
    //    }
}
