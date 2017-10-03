#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QImage>

#include "image.h"

class ImageConverter
{
public:
    static Image QImageToImage(const QImage &qImage);
};

#endif // IMAGECONVERTER_H
