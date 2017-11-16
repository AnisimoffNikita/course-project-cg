#include "light.h"

Light::Light()
{

}


void Light::draw(Renderer &)
{
}

void Light::transform(const Transformation &transformation)
{
    transformation.transform(position);
}

bool Light::isCamera()
{
    return false;
}

bool Light::isLight()
{
    return true;
}
