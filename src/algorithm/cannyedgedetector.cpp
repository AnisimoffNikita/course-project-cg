#include "cannyedgedetector.h"

#include "src/math/math.h"
#include "src/image/imageconverter.h"

CannyEdgeDetector::CannyEdgeDetector()
{

}

CannyEdgeDetector::~CannyEdgeDetector()
{

}

void CannyEdgeDetector::process(Image &image)
{
    this->image = ImageConverter::ImageToGrayscalImage(image);
    gaussianBlur(5);
    gradients();
    nonMaxSuppression();
    doubleThreshold();
    hysteresis();
    image = ImageConverter::GrayscaleImageToImage(this->image);
}

void CannyEdgeDetector::gaussianBlur(int kernelSize)
{
    GrayscaleImage saved(image);
    float kernel[kernelSize][kernelSize];
    float norm = 0;
    for (int i = 0; i < kernelSize; i++)
        for (int j = 0; j < kernelSize; j++)
        {
            kernel[i][j] = Math::Gauss2(1.4, i-2, j-2);
            norm += kernel[i][j];
        }

    uint32 height = image.getHeight();
    uint32 width = image.getWidth();

    uint32 pixelPosX;
    uint32 pixelPosY;
    float result;

    for (uint32 y = 0; y < height; y++)
    {
        for (uint32 x = 0; x < width; x++)
        {
            result = 0;

            for (int i = 0; i < kernelSize; i++)
            {
                for (int j = 0; j < kernelSize; j++)
                {
                    pixelPosX = (x + j - kernelSize / 2 + width)%width;
                    pixelPosY = (y + i - kernelSize / 2 + height)%height;

                    uint8 color = saved.at(pixelPosY, pixelPosX);

                    float kernelVal = kernel[i][j];

                    result += color * kernelVal;
                }
            }

            result = Math::Clamp<float>(result, 0, 255);

            image.set(y, x, static_cast<uint8>(result));
        }
    }
}

void CannyEdgeDetector::gradients()
{
    GrayscaleImage saved(image);
    constexpr int kernelSize = 3;
    float gx[kernelSize][kernelSize] = {{1,0,-1},{2,0,-2},{1,0,-1}};
    float gy[kernelSize][kernelSize] = {{1,2,1},{0,0,0},{-1,-2,-1}};

    int height = image.getHeight();
    int width = image.getWidth();

    int pixelPosX;
    int pixelPosY;

    directions = GrayscaleImage(height, width);

    float resultX;
    float resultY;
    float result;
    for (int y = 0; y < height; y++)
    {
        for (int x =0; x < width; x++)
        {
            resultX = resultY = 0;
            for (int i = 0; i < kernelSize; i++)
            {
                for (int j = 0; j < kernelSize; j++)
                {
                    pixelPosX = (x + j - kernelSize / 2 + width)%width;
                    pixelPosY = (y + i - kernelSize / 2 + height)%height;

                    uint8 color = saved.at(pixelPosY, pixelPosX);

                    float gxVal = gx[i][j];
                    float gyVal = gy[i][j];

                    resultX += color * gxVal;

                    resultY += color * gyVal;
                }
            }

            result = sqrt(resultX * resultX + resultY * resultY);


            float angle;
            if (resultX == 0)
            {
                if (resultY == 0)
                    angle = 0;
                else
                    angle = 90;
            }
            else
            {
                angle = atan2(resultY, resultX) * 180.0 / M_PI;
            }

            if ((angle > -22.5 && angle <= 22.5) ||
                    (angle > 157.5 && angle <= -157.5) ||
                    (angle > -202.5 && angle <= -157.5))
            {
                directions.set(y, x, 0);
            }
            else if ((angle > 22.5 && angle <= 67.5) ||
                       (angle > -157.5 && angle <= -112.5))
            {
                directions.set(y, x, 45);
            }
            else if ((angle > 67.5 && angle <= 112.5) ||
                       (angle > -112.5 && angle <= -67.5))
            {
                directions.set(y, x, 90);
            }
            else if ((angle > 112.5 && angle <= 157.5) ||
                       (angle > -67.5 && angle <= -22.5))
            {
                directions.set(y, x, 135);
            }

            result = Math::Clamp<float>(result,0,255);
            image.set(y, x, static_cast<uint8>(result));
        }
    }


}

void CannyEdgeDetector::nonMaxSuppression()
{
    uint8 pixel1 = 0;
    uint8 pixel2 = 0;
    uint8 pixel;

    for (uint32 y = 1; y < image.getHeight() - 1; y++)
    {
        for (uint32 x = 1; x < image.getWidth() - 1; x++)
        {
            if (directions.at(y,x) == 90)
            {
                pixel1 = image.at(y + 1, x);
                pixel2 = image.at(y - 1, x);
            }
            else if (directions.at(y,x) == 135)
            {
                pixel1 = image.at(y + 1, x - 1);
                pixel2 = image.at(y - 1, x + 1);
            }
            else if (directions.at(y,x) == 0)
            {
                pixel1 = image.at(y, x - 1);
                pixel2 = image.at(y, x + 1);
            }
            else if (directions.at(y, x) == 45)
            {
                pixel1 = image.at(y + 1, x + 1);
                pixel2 = image.at(y - 1, x - 1);
            }
            pixel = image.at(y, x);
            if (pixel > pixel1 && pixel > pixel2)
            {
                image.set(y, x, pixel);
            }
            else
            {
                image.set(y, x, 0);
            }
        }
    }

}

void CannyEdgeDetector::doubleThreshold()
{
    uint8 pixel;
    constexpr float max = 80;
    constexpr float min = 60;
    for (uint32 y = 0; y < image.getHeight(); y++)
    {
        for (uint32 x = 0; x < image.getWidth(); x++)
        {
            pixel = image.at(y, x);
            if (pixel > max)
                image.set(y, x, 255);
            else if (pixel < min)
                image.set(y, x, 0);
            else
                image.set(y, x, 127);
        }
    }
}

void CannyEdgeDetector::hysteresis()
{
    for(uint32 y = 1; y < image.getHeight() - 1; ++y)
    {
        for(uint32 x = 1; x < image.getWidth() - 1; ++x)
        {
            if(image.at(y,x) == 255)
            {
                hysteresisRecursive(y, x);
            }
        }
    }
    for (uint32 y = 0; y < image.getHeight(); y++)
    {
        for (uint32 x = 0; x < image.getWidth(); x++)
        {
            if(image.at(y,x) != 255)
            {
                image.set(y, x, 0);
            }
        }
    }
}

void CannyEdgeDetector::hysteresisRecursive(uint32 y, uint32 x)
{
    if(image.at(y,x) != 255)
    {
        image.set(y, x, 255);
    }

    if(y < image.getHeight() - 1 && x < image.getWidth() - 1 && image.at(y + 1, x + 1)== 127)
    {
        hysteresisRecursive(y + 1, x + 1);
    }
    if(x < image.getWidth() - 1 && image.at(y, x + 1) == 127)
    {
        hysteresisRecursive(y, x+1);
    }
    if(y < image.getHeight() - 1 && image.at(y + 1, x) == 127)
    {
        hysteresisRecursive(y + 1, x);
    }
    if(y > 1 && x < image.getWidth() - 1 && image.at(y - 1, x + 1) == 127)
    {
        hysteresisRecursive(y - 1, x + 1);
    }
    if(y < image.getHeight() - 1 && x > 1 && image.at(y + 1, x - 1) == 127)
    {
        hysteresisRecursive(y + 1, x - 1);
    }
    if(y > 1 && x > 1 && image.at(y - 1, x - 1) == 127)
    {
        hysteresisRecursive(y - 1, x - 1);
    }
    if(x > 1 && image.at(y, x - 1) == 127)
    {
        hysteresisRecursive(y, x - 1);
    }
    if(y > 1 && image.at(y - 1, x) == 127)
    {
        hysteresisRecursive(y - 1, x);
    }
}
