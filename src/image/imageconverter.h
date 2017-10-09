#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QImage>

#include "image.h"
#include "grayscaleimage.h"

class ImageConverter
{
public:
    static Image QImageToImage(const QImage &qImage);
    static QImage ImageToQImage(const Image &image);

    static GrayscaleImage ImageToGrayscalImage(const Image &image);
    static Image GrayscaleImageToImage(const GrayscaleImage &image);

private:
    static uint8 getGrayscale(const Color &color);
};

#endif // IMAGECONVERTER_H
