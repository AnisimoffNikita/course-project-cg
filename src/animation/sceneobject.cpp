#include "sceneobject.h"


Vertex SceneObject::getPosition() const
{
    return _position;
}

void SceneObject::setPosition(const Vertex &value)
{
    _position = value;
}

int32 SceneObject::getTag() const
{
    return _tag;
}

void SceneObject::setTag(const int32 &tag)
{
    _tag = tag;
}
