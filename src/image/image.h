#ifndef IMAGE_H
#define IMAGE_H


#include <QImage>

#include <memory>

#include "src/number.h"
#include "color.h"

class ImageConverter;

class Image
{
public:
    Image();
    Image(const Image &image);
    Image(Image &&image);

    Image &operator =(const Image &image);
    Image &operator =(Image &&image);

public:
    const Color &at(uint32 i, uint32 j) const;
    void set(uint32 i, uint32 j, const Color &color);

    uint32 getHeight() const;
    void setHeight(uint32 value);

    uint32 getWidth() const;
    void setWidth(uint32 value);

private:
    std::unique_ptr<Color[]> data;
    uint32 width, height;

    friend class ImageConverter;
    friend class GrayscaleConverter;
};


#endif // IMAGE_H
