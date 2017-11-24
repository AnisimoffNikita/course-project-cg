#include "sceneobject.h"


SceneObject::SceneObject(const Vec3 &position):
    position(position)
{
}

const Vec3 &SceneObject::getPosition()
{
    return position;
}

void SceneObject::setPosition(const Vec3 &value)
{
    position = value;
}
