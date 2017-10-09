#include "cannyedgedetector.h"

#include "src/math/math.h"

CannyEdgeDetector::CannyEdgeDetector()
{

}

CannyEdgeDetector::~CannyEdgeDetector()
{

}

void CannyEdgeDetector::process(Image &image)
{
    this->image = image;
    gaussianBlur(5);
    gradients();
    nonMaxSuppression();
    doubleThreshold();
    hysteresis();
    image = this->image;
}

void CannyEdgeDetector::gaussianBlur(int kernelSize)
{
    Image saved(image);
    float kernel[kernelSize][kernelSize];
    float norm = 0;
    for (int i = 0; i < kernelSize; i++)
        for (int j = 0; j < kernelSize; j++)
        {
            kernel[i][j] = Math::Gauss2(1.4, i-2, j-2);
            norm += kernel[i][j];
        }

    int height = image.getHeight();
    int width = image.getWidth();

    int pixelPosX;
    int pixelPosY;

    for (int y = kernelSize / 2; y < height - kernelSize / 2; y++)
    {
        for (int x = kernelSize / 2; x < width - kernelSize / 2; x++)
        {
            float rSum = 0, gSum = 0, bSum = 0;

            for (int i = 0; i < kernelSize; i++)
            {
                for (int j = 0; j < kernelSize; j++)
                {
                    pixelPosX = x + j - kernelSize / 2;
                    pixelPosY = y + i - kernelSize / 2;

                    uint8 red = saved.at(pixelPosY, pixelPosX).getRed();
                    uint8 green = saved.at(pixelPosY, pixelPosX).getGreen();
                    uint8 blue = saved.at(pixelPosY, pixelPosX).getBlue();

                    float kernelVal = kernel[i][j];

                    rSum += red * kernelVal;
                    gSum += green * kernelVal;
                    bSum += blue * kernelVal;
                }
            }

            rSum = rSum > 255 ? 255 : rSum;
            rSum = rSum < 0 ? 0 : rSum;

            gSum = gSum > 255 ? 255 : gSum;
            gSum = gSum < 0 ? 0 : gSum;

            bSum = bSum > 255 ? 255 : bSum;
            bSum = bSum < 0 ? 0 : bSum;

            Color color(rSum, gSum, bSum);
            image.set(pixelPosY, pixelPosX, color);
        }
    }
}

void CannyEdgeDetector::gradients()
{
    Image saved(image);
    constexpr int kernelSize = 3;
    float gx[kernelSize][kernelSize] = {{1,0,-1},{2,0,-2},{1,0,-1}};
    float gy[kernelSize][kernelSize] = {{1,2,1},{0,0,0},{-1,-2,-1}};

    int height = image.getHeight();
    int width = image.getWidth();

    int pixelPosX;
    int pixelPosY;

    directions.resize(image.getHeight());
    for (auto &row : directions)
    {
        row.resize(image.getWidth());
    }

    for (int y = kernelSize / 2; y < height - kernelSize / 2; y++)
    {
        for (int x = kernelSize / 2; x < width - kernelSize / 2; x++)
        {
            float rxSum = 0;//, gxSum = 0, bxSum = 0;
            float rySum = 0;//, gySum = 0, bySum = 0;
            float rSum = 0;//, gSum = 0, bSum = 0;

            for (int i = 0; i < kernelSize; i++)
            {
                for (int j = 0; j < kernelSize; j++)
                {
                    pixelPosX = x + j - kernelSize / 2;
                    pixelPosY = y + i - kernelSize / 2;

                    uint8 red = saved.at(pixelPosY, pixelPosX).getRed();/*
                    uint8 green = saved.at(pixelPosY, pixelPosX).getGreen();
                    uint8 blue = saved.at(pixelPosY, pixelPosX).getBlue();*/

                    float gxVal = gx[i][j];
                    float gyVal = gy[i][j];

                    rxSum += red * gxVal;/*
                    gxSum += green * gxVal;
                    bxSum += blue * gxVal;*/

                    rySum += red * gyVal;/*
                    gySum += green * gyVal;
                    bySum += blue * gyVal;*/
                }
            }

            rSum = abs(rxSum) + abs(rySum);
            rSum = rSum > 255 ? 255 : rSum;
            rSum = rSum < 0 ? 0 : rSum;

            float angle;
            if ((rxSum != 0.0) || (rySum != 0.0))
            {
                angle = atan2(rxSum, rySum) * 180.0 / M_PI;
            } else
            {
                angle = 0.0;
            }
            if (((angle > -22.5) && (angle <= 22.5)) ||
                    ((angle > 157.5) && (angle <= -157.5)))
            {
                directions[y][x] = 0;
            }
            else if (((angle > 22.5) && (angle <= 67.5)) ||
                       ((angle > -157.5) && (angle <= -112.5)))
            {
                directions[y][x] = 45;
            }
            else if (((angle > 67.5) && (angle <= 112.5)) ||
                       ((angle > -112.5) && (angle <= -67.5)))
            {
                directions[y][x] = 90;
            }
            else if (((angle > 112.5) && (angle <= 157.5)) ||
                       ((angle > -67.5) && (angle <= -22.5)))
            {
                directions[y][x] = 135;
            }

            Color color(rSum, rSum, rSum);
            image.set(pixelPosY, pixelPosX, color);
        }
    }


}

void CannyEdgeDetector::nonMaxSuppression()
{
    Color pixel_1 = 0;
    Color pixel_2 = 0;
    Color pixel;

    for (uint32 x = 1; x < image.getHeight() - 1; x++)
    {
        for (uint32 y = 1; y < image.getWidth() - 1; y++)
        {
            if (directions[x][y] == 0)
            {
                pixel_1 = image.at(x + 1, y);
                pixel_2 = image.at(x - 1, y);
            }
            else if (directions[x][y] == 45)
            {
                pixel_1 = image.at(x + 1, y - 1);
                pixel_2 = image.at(x - 1, y + 1);
            }
            else if (directions[x][y] == 90)
            {
                pixel_1 = image.at(x, y - 1);
                pixel_2 = image.at(x, y + 1);
            }
            else if (directions[x][y] == 135)
            {
                pixel_1 = image.at(x + 1, y + 1);
                pixel_2 = image.at(x - 1, y - 1);
            }
            pixel = image.at(x, y);
            if ((pixel.getRed() > pixel_1.getRed()) && (pixel.getRed() > pixel_2.getRed()))
            {
                image.set(x, y, pixel);
            }
            else
            {
                image.set(x, y, Color(0,0,0));
            }
        }
    }

}

void CannyEdgeDetector::doubleThreshold()
{
    Color pixel;
    constexpr float max = 140;
    constexpr float min = 100;
    for (uint32 y = 0; y < image.getHeight(); y++)
    {
        for (uint32 x = 0; x < image.getWidth(); x++)
        {
            pixel = image.at(y, x);
            float color = pixel.getRed();
            if (color > max)
                image.set(y, x, Color(255,255,255));
            else if (color < min)
                image.set(y, x, Color(0,0,0));
            else
                image.set(y, x, Color(127,127,127));
        }
    }
}

void CannyEdgeDetector::hysteresis()
{
    for(uint32 y = 1; y < image.getHeight() - 1; ++y)
    {
        for(uint32 x = 1; x < image.getWidth() - 1; ++x)
        {
            if(image.at(y,x).getRed() == 255)
            {
                hysteresisRecursive(y, x);
            }
        }
    }
}

void CannyEdgeDetector::hysteresisRecursive(uint32 y, uint32 x)
{
    image.set(y,x,Color(255,255,255));

    if(y < image.getHeight() - 1 && x < image.getWidth() - 1 && image.at(y + 1, x + 1).getRed() == 127)
    {
        hysteresisRecursive(y + 1, x + 1);
    }
    if(x < image.getWidth() - 1 && image.at(y, x + 1).getRed() == 127)
    {
        hysteresisRecursive(y, x+1);
    }
    if(y < image.getHeight() - 1 && image.at(y + 1, x).getRed() == 127)
    {
        hysteresisRecursive(y + 1, x);
    }
    if(y > 1 && x < image.getWidth() - 1 && image.at(y - 1, x + 1).getRed() == 127)
    {
        hysteresisRecursive(y - 1, x + 1);
    }
    if(y < image.getHeight() - 1 && x > 1 && image.at(y + 1, x - 1).getRed() == 127)
    {
        hysteresisRecursive(y + 1, x - 1);
    }
    if(y > 1 && x > 1 && image.at(y - 1, x - 1).getRed() == 127)
    {
        hysteresisRecursive(y - 1, x - 1);
    }
    if(x > 1 && image.at(y, x - 1).getRed() == 127)
    {
        hysteresisRecursive(y, x - 1);
    }
    if(y > 1 && image.at(y - 1, x).getRed() == 127)
    {
        hysteresisRecursive(y - 1, x);
    }
}
