#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QImage>

#include "image.h"

class ImageConverter
{
public:
    static Image QImageToImage(const QImage &qImage);
    static QImage ImageToQImage(const Image &image);
};

#endif // IMAGECONVERTER_H
