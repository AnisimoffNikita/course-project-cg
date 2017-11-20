#include "light.h"
#include "transformation.h"

Light::Light(const Vertex &position) :
    SceneObject(position)
{

}

void Light::draw(std::unique_ptr<Renderer> &)
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
