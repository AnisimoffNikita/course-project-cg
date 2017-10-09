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
            Color &pixel = image.data[i*image.width + j];
            QColor target = qImage.pixelColor(j, i);
            pixel.setRed(target.red());
            pixel.setGreen(target.green());
            pixel.setBlue(target.blue());
        }
    return image;
}

QImage ImageConverter::ImageToQImage(const Image &image)
{
    QImage qImage(image.width, image.height, QImage::Format_RGB32);

    for (uint32 i = 0; i < image.height; i++)
        for (uint32 j = 0; j < image.width; j++)
        {
            Color &pixel = image.data[i*image.width + j];
            QColor color(pixel.getRed(),
                         pixel.getBlue(),
                         pixel.getGreen());
            qImage.setPixelColor(j,i,color);
        }
    return qImage;
}
