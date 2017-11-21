#include "imageconverter.h"


Image ImageConverter::QImageToImage(const QImage &qImage)
{
    Image image;
    image.width = qImage.width();
    image.height = qImage.height();
    image.data = std::make_unique<Color[]>(image.width * image.height);

    for (uint32 i = 0; i < image.height; i++)
        for (uint32 j = 0; j < image.width; j++)
        {
            Color &pixel = image.data[i * image.width + j];
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
            Color &pixel = image.data[i * image.width + j];
            QColor color(pixel.getRed(),
                         pixel.getGreen(),
                         pixel.getBlue());
            qImage.setPixelColor(j, i, color);
        }

    return qImage;
}

GrayscaleImage ImageConverter::ImageToGrayscalImage(const Image &image)
{
    GrayscaleImage grayscaleImage(image.getHeight(), image.getWidth());

    for (uint32 i = 0; i < image.width * image.height; i++)
    {
        grayscaleImage.data[i] = getGrayscale(image.data[i]);
    }

    return grayscaleImage;
}

uint8 ImageConverter::getGrayscale(const Color &color)
{
    uint8 gray = color.getRed() * 0.299 + color.getGreen() * 0.587 + color.getBlue()
                 * 0.114;
    return gray;
}


Image ImageConverter::GrayscaleImageToImage(const GrayscaleImage
        &grayscaleImage)
{
    Image image(grayscaleImage.height, grayscaleImage.width);

    for (uint32 i = 0; i < grayscaleImage.width * grayscaleImage.height; i++)
    {
        image.data[i].setGray(grayscaleImage.data[i]);
    }

    return image;
}
