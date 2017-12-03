#include "light.h"
#include "transformation.h"

Light::Light(const Vec3 &position, float intensity) :
    SceneObject(position),
    intensity(intensity)
{
}

void Light::draw(std::unique_ptr<Renderer> &)
{
}

void Light::transform(Transformation &transformation)
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
