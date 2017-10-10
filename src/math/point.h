#ifndef POINT_H
#define POINT_H

#include "src/number.h"

class Point
{
public:
    Point();
    Point(int x, int y);

    int32 getX() const;
    void setX(const int32 &value);

    int32 getY() const;
    void setY(const int32 &value);

private:
    int32 x;
    int32 y;
};

#endif // POINT_H
