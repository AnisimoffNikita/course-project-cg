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
        buffer[i].resize(width);
}

void ZBuffer::init()
{
    int min = numeric_limits<int>::min();
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            buffer[i][j] = min;

}

int ZBuffer::get(int i, int j)
{
    return buffer[i][j];
}

void ZBuffer::set(int i, int j, int value)
{
    buffer[i][j] = value;
}
