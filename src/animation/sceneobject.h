#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <vector>
#include <memory>

#include "src/math/vec3.h"
#include "src/math/matrix.h"
#include "src/animation/rendercontext.h"
#include "src/animation/transformation.h"

class SceneObject;
using SharedSceneObject = std::shared_ptr<SceneObject>;

class SceneObject
{
public:
    SceneObject() = default;
    virtual ~SceneObject() = default;

    int32 getTag() const;
    void setTag(const int32 &tag);

    virtual Vertex getPosition() const;
    virtual void setPosition(const Vertex &value);

    virtual void draw(const RenderContext &render) = 0;
    virtual void transform(const Transformation &transformation) = 0;

    virtual bool isCamera() = 0;
    virtual bool isLight() = 0;


private:
    Vertex _position;
    int32 _tag;
};


#endif // SCENEOBJECT_H
