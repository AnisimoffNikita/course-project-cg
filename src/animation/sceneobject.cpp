#include "sceneobject.h"


SceneObject::SceneObject(const Vertex &position):
    position(position)
{
}

Vertex SceneObject::getPosition() const
{
    return position;
}

void SceneObject::setPosition(const Vertex &value)
{
    position = value;
}
