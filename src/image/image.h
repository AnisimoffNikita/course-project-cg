#ifndef IMAGE_H
#define IMAGE_H


#include <QImage>

#include <memory>
#include "imagebase.h"

#include "src/number.h"
#include "color.h"

class ImageConverter;

class Image : public ImageBase<Color>
{
public:
    using ImageBase<Color>::ImageBase;

    friend class ImageConverter;
    friend class GrayscaleConverter;
};


#endif // IMAGE_H
