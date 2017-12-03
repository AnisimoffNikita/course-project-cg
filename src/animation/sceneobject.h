#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <vector>
#include <memory>

#include "src/math/vec3.h"

class Renderer;
class Transformation;

class SceneObject
{
public:
    SceneObject() = default;
    SceneObject(const Vec3 &position);
    virtual ~SceneObject() = default;


    virtual const Vec3 &getPosition();
    virtual void setPosition(const Vec3 &value);

    virtual void draw(std::unique_ptr<Renderer> &render) = 0;
    virtual void transform(Transformation &transformation) = 0;

    virtual bool isCamera() = 0;
    virtual bool isLight() = 0;


protected:
    Vec3 position;
};

using SharedSceneObject = std::shared_ptr<SceneObject>;

#endif // SCENEOBJECT_H
