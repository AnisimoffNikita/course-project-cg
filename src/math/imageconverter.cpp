#include "imageconverter.h"


Image ImageConverter::QImageToImage(const QImage &qImage)
{
    Image image;
    image.width = qImage.width();
    image.height = qImage.height();
    image.data = std::make_unique<Color[]>(image.width*image.height);
    for (uint32 i = 0; i < image.height; i++)
        for (uint32 j = 0; j < image.width; j++)
        {
            image.data[i*image.width + j].setRed(qImage.pixelColor(j, i).red());
            image.data[i*image.width + j].setGreen(qImage.pixelColor(j, i).green());
            image.data[i*image.width + j].setBlue(qImage.pixelColor(j, i).blue());
        }
    return image;
}
