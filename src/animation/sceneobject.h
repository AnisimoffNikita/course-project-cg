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
    SceneObject(const Vertex &position);
    virtual ~SceneObject() = default;


    virtual Vertex getPosition() const;
    virtual void setPosition(const Vertex &value);

    virtual void draw(std::unique_ptr<Renderer> &render) = 0;
    virtual void transform(const Transformation &transformation) = 0;

    virtual bool isCamera() = 0;
    virtual bool isLight() = 0;


protected:
    Vertex position;
};

using SharedSceneObject = std::shared_ptr<SceneObject>;

#endif // SCENEOBJECT_H
