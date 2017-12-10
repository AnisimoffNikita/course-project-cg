#include "cylindersizecalculator.h"

#include <cmath>
#include "src/math/math.h"

CylinderSizeCalculator::CylinderSizeCalculator()
{
}

CylinderSizeCalculator::~CylinderSizeCalculator()
{
}

CylinderSize CylinderSizeCalculator::evaluate(const Lines &lines)
{
    this->lines = lines;
    findEdges();

    if (this->lines.size() == 0)
    {
        return CylinderSize(-1, -1);
    }

    if (this->lines.size() > 2)
    {
        return CylinderSize(-2, -2);
    }

    calculateSize();
    return size;
}

bool CylinderSizeCalculator::calibrate(const std::vector<Line> &inLines,
                                       float distance, float radius, float height)
{
    lines = inLines;
    this->distance = distance;
    findEdges();

    if (this->lines.size() == 0)
    {
        return false;
    }

    if (this->lines.size() > 2)
    {
        return false;
    }

    float visibleEdge = distance - (radius + radius * radius /
                                    (distance - radius));
    float localFactor = height / lines[0].length();
    factor = localFactor * (distance / visibleEdge);
    return true;
}

bool CylinderSizeCalculator::calibrate(float distance, float scale)
{
    this->distance = distance;
    factor = scale;
    return true;
}

void CylinderSizeCalculator::findEdges()
{
    std::vector<Line> result;

    for (uint32 i = 0; i < lines.size(); i++)
    {
        for (uint32 j = i + 1; j < lines.size(); j++)
        {
            int32 dx1 = lines[i].getP1().getX() - lines[i].getP2().getX();
            int32 dy1 = lines[i].getP1().getY() - lines[i].getP2().getY();
            int32 dx2 = lines[j].getP1().getX() - lines[j].getP2().getX();
            int32 dy2 = lines[j].getP1().getY() - lines[j].getP2().getY();

            if ((dx1 >= 0 && dy1 >= 0 && dx2 <= 0 && dy2 <= 0) ||
                    (dx1 <= 0 && dy1 <= 0 && dx2 >= 0 && dy2 >= 0) ||
                    (dx1 >= 0 && dy1 <= 0 && dx2 <= 0 && dy1 >= 0) ||
                    (dx1 <= 0 && dy1 >= 0 && dx2 >= 0 && dy1 <= 0))
            {
                dx2 *= -1;
                dy2 *= -1;
            }

            int32 eps = 10;
            float maxWidth = 0;

            if (fabs(dx1 - dx2) < eps && fabs(dy1 - dy2) < eps)
            {
                int32 dx3 = lines[i].getP1().getX() - lines[j].getP1().getX();
                int32 dy3 = lines[i].getP1().getY() - lines[j].getP1().getY();
                int32 dx4 = lines[i].getP2().getX() - lines[j].getP2().getX();
                int32 dy4 = lines[i].getP2().getY() - lines[j].getP2().getY();

                if (fabs(dx3 - dx4) < eps && fabs(dy3 - dy4) < eps)
                {
                    uint32 width = sqrt(dx3 * dx3 + dy3 * dy3);

                    if (width > maxWidth)
                    {
                        maxWidth = width;
                        result.push_back(lines[i]);
                        result.push_back(lines[j]);
                    }
                }
            }
        }
    }

    lines = result;
}

void CylinderSizeCalculator::calculateSize()
{
    int32 dx = lines[0].getP1().getX() - lines[1].getP1().getX();
    int32 dy = lines[0].getP1().getY() - lines[1].getP1().getY();
    float inDiam = sqrt(dx * dx + dy * dy);
    Math::Func f = [inDiam, this](float r)
    {
        auto visibleDiam = 2 * r * pow(1 - pow(r / (distance - r), 2), 0.5);
        auto visibleDist = distance - (r + r * r / (distance - r));
        auto localFactor = factor * (visibleDist / distance);
        auto evalDiam = visibleDiam / localFactor;
        return evalDiam - inDiam;
    };
    float radius = Math::Bisection(distance * 0.01, distance * 0.5, f);
    auto localFactor = factor * ((distance - (radius + radius * radius /
                                  (distance - radius))) / distance);
    float height = localFactor * (lines[0].length() + lines[1].length()) / 2;
    size.setHeight(height);
    size.setRadius(radius);
}
