#ifndef CYLINDERSIZE_H
#define CYLINDERSIZE_H


class CylinderSize
{
public:
    CylinderSize(float height = 0, float radius = 0);

    float getRadius() const;
    void setRadius(float value);

    float getHeight() const;
    void setHeight(float value);

private:
    float height;
    float radius;
};

#endif // CYLINDERSIZE_H
