#include "zbuffer.h"

#include <limits>

ZBuffer::ZBuffer()
{
}

void ZBuffer::setSize(int32 w, int32 h)
{
    width = w;
    height = h;
    buffer.resize(height * width);
}

void ZBuffer::init()
{
    unsigned min = ~0;

    for (int32 i = 0; i < height * width; i++)
    {
        buffer[i] = min;
    }
}

float ZBuffer::get(int32 x, int32 y)
{
    return buffer[y * width + x];
}

void ZBuffer::set(int32 x, int32 y, float value)
{
    buffer[y * width + x] = value;
}
