#ifndef CYLINDERSIZE_H
#define CYLINDERSIZE_H


class CylinderSize
{
public:
    CylinderSize(double height = 0, double radius = 0);

    double getRadius() const;
    void setRadius(double value);

    double getHeight() const;
    void setHeight(double value);

private:
    double height;
    double radius;
};

#endif // CYLINDERSIZE_H
