#include "grayscaleconverter.h"

GrayscaleConverter::GrayscaleConverter()
{

}

GrayscaleConverter::~GrayscaleConverter()
{

}

void GrayscaleConverter::process(Image &image)
{
    for (uint32 i = 0; i < image.width*image.height; i++)
        image.data[i] = getGrayscale(image.data[i]);
}

Color GrayscaleConverter::getGrayscale(const Color &color)
{
    uint8 gray = color.getRed()*0.299+color.getGreen()*0.587+color.getBlue()*0.114;
    return Color(gray);
}
