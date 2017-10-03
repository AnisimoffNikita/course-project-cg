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

QImage ImageConverter::ImageToQImage(const Image &image)
{
    QImage qImage(image.width, image.height, QImage::Format_RGB32);

    for (uint32 i = 0; i < image.height; i++)
        for (uint32 j = 0; j < image.width; j++)
        {
            QColor color(image.data[i*image.width + j].getRed(),
                         image.data[i*image.width + j].getBlue(),
                         image.data[i*image.width + j].getGreen());
            qImage.setPixelColor(j,i,color);
        }
}
