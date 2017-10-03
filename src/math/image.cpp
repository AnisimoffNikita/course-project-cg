#include "image.h"

Image::Image() :
    data(nullptr),
    width(0),
    height(0)
{
}

Image::Image(const Image &image) :
    width(image.width),
    height(image.height)
{
    data = std::make_unique<Color[]>(width*height);
    for (uint32 i = 0; i < width*height; i++)
        data[i] = image.data[i];
}

Image::Image(Image &&image) :
    data(std::move(image.data)),
    width(image.width),
    height(image.height)
{
    image.data = nullptr;
}


const Color &Image::at(uint32 i, uint32 j) const
{
    return data[i*width+j];
}

void Image::set(uint32 i, uint32 j, const Color &color)
{
    data[i*width+j] = color;
}

uint32 Image::getHeight() const
{
    return height;
}

void Image::setHeight(uint32 value)
{
    height = value;
}

uint32 Image::getWidth() const
{
    return width;
}

void Image::setWidth(uint32 value)
{
    width = value;
}
