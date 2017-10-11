#include "houghtransform.h"

#include "src/image/imageconverter.h"
#include "src/math/math.h"


HoughTransform::HoughTransform(uint32 threshold):
    threshold(threshold)
{

}

HoughTransform::~HoughTransform()
{

}

std::vector<Line>  HoughTransform::process(Image &image)
{
    this->image = ImageConverter::ImageToGrayscalImage(image);

    lines.clear();
    accumulator.clear();

    fillAccumulator();
    getLines();

    Image color = ImageConverter::GrayscaleImageToImage(this->image);

    drawLines(color);

    image = color;

    return lines;
}

void HoughTransform::fillAccumulator()
{
    uint32 height = image.getHeight();
    uint32 width = image.getWidth();

    accumulatorHeight = static_cast<uint32>(sqrt(height*height+width*width)+1);
    accumulatorWidth = 180;

    accumulator.resize(accumulatorHeight*accumulatorWidth);

    double centerX = width/2;
    double centerY = height/2;

    for(uint32 y = 0; y < height; y++)
    {
        for(uint32 x = 0; x < width; x++)
        {
            if( image.at(y, x) == 255 )
            {
                for(uint32 theta = 0; theta < 180; theta++)
                {
                    double thetaRad = Math::ToRadians(theta);
                    double rho = (x - centerX) * cos(thetaRad) + (y - centerY) * sin(thetaRad);
                    accumulator[static_cast<int>(rho + accumulatorHeight/2) * accumulatorWidth + theta].emplace_back(x, y);
                }
            }
        }
    }
}

void HoughTransform::getLines()
{

    int32 signedAccHeight = static_cast<int32>(accumulatorHeight);
    int32 signedAccWidth = static_cast<int32>(accumulatorWidth);

    for(int32 rho = 0; rho < signedAccHeight; rho++)
    {
        for(int32 theta = 0; theta < signedAccWidth; theta++)
        {
            if(accumulator[rho*accumulatorWidth + theta].size() >= threshold)
            {
                uint32 max = accumulator[rho*accumulatorWidth + theta].size();

                //TODO
                for(int32 ly=-4;ly<=4;ly++)
                {
                    for(int32 lx=-4;lx<=4;lx++)
                    {
                        if( (ly+rho>=0 && ly+rho<signedAccHeight) && (lx+theta>=0 && lx+theta<signedAccWidth) )
                        {
                            if( accumulator[( (rho+ly)*signedAccWidth) + (theta+lx)].size() > max )
                            {
                                max = accumulator[( (rho+ly)*accumulatorWidth) + (theta+lx)].size();
                                ly = lx = 5;
                            }
                        }
                    }
                }

                if(max > accumulator[rho*accumulatorWidth + theta].size())
                    continue;

                Points &lineAcc = accumulator[rho*accumulatorWidth + theta];
                int32 minItem = 0, maxItem = 0;
                for (uint32 i = 1; i < lineAcc.size(); i++)
                {
                    if (lineAcc[i].getX() < lineAcc[minItem].getX())
                        minItem = i;
                    else if (lineAcc[i].getX() > lineAcc[maxItem].getX())
                        maxItem = i;
                }
                if (minItem == maxItem)
                {
                    minItem = maxItem = 0;
                    for (uint32 i = 1; i < lineAcc.size(); i++)
                    {
                        if (lineAcc[i].getY() < lineAcc[minItem].getY())
                            minItem = i;
                        else if (lineAcc[i].getY() > lineAcc[maxItem].getY())
                            maxItem = i;
                    }
                }

                lines.emplace_back(lineAcc[minItem], lineAcc[maxItem]);


            }
        }
    }
}

void HoughTransform::drawLines(Image &color)
{
    for (const Line &line : lines)
    {
        brezenhem(color, line);
    }
}

void HoughTransform::brezenhem(Image &color, const Line &line)
{
    Point p1 = line.getP1(), p2 = line.getP2();
    int32 x1 = p1.getX(), y1 = p1.getY();
    int32 x2 = p2.getX(), y2 = p2.getY();
    if (x1 == x2 && y1 == y2)
    {
        color.set(y1, x1, Color(255,0,0));
    }
    int32 dx = x2 - x1, dy = y2 - y1;
    int32 sx = Math::sgn(dx), sy = Math::sgn(dy);
    dx = abs(dx); dy = abs(dy);
    bool flag = dy > dx;
    if (flag)
    {
        std::swap(dx, dy);
    }
    int32 f = (dy<<1) - dx;
    int32 x = x1, y = y1;

    if (flag)
    {
        for (int32 i = 0; i < dx; i++)
        {
            color.set(y, x, Color(255,0,0));
            if (f > 0)
            {
                x += sx;
                f -= dx*2;
            }
            y += sy;
            f += dy*2;
        }
    }
    else
    {
        for (int32 i = 0; i < dx; i++)
        {
            color.set(y, x, Color(255,0,0));
            if (f > 0)
            {
                y += sy;
                f -= dx*2;
            }
            x += sx;
            f += dy*2;
        }
    }
    color.set(y, x, 127);
}
