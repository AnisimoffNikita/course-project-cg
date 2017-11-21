#include "zbuffer.h"

#include <limits>

ZBuffer::ZBuffer()
{
}

void ZBuffer::setSize(int w, int h)
{
    width = w;
    height = h;
    buffer.resize(height);

    for (int i = 0; i < height; i++)
    {
        buffer[i].resize(width);
    }
}

void ZBuffer::init()
{
    int min = numeric_limits<int>::min();

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = min;
        }
}

int ZBuffer::get(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        return buffer[y][x];
    }
    else
    {
        return numeric_limits<int>::min();
    }
}

void ZBuffer::set(int x, int y, int value)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        buffer[y][x] = value;
    }
}
