#include "sceneobject.h"


SceneObject::SceneObject(const Vec3 &position):
    position(position)
{
}

Vec3 SceneObject::getPosition() const
{
    return position;
}

void SceneObject::setPosition(const Vec3 &value)
{
    position = value;
}
