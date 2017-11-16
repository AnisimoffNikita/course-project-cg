#ifndef CAMERA_H
#define CAMERA_H

#include "sceneobject.h"

class Camera : public SceneObject
{
public:
    Camera(const Vertex &position, const Vertex &lookAt, const Vertex &up, const Mat4 &projection);

    virtual void draw(Renderer &) override;
    virtual void transform(const Transformation &transformation) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;

    virtual void setPosition(const Vertex &value) override;
    virtual void setLookAt(const Vertex &target);
    virtual Mat4 getPVMatrix();

protected:
    void updateViewMatrix();

    Vertex lookAt;
    Vertex up;
    Mat4 viewMatrix;
    Mat4 projectionMatrix;

};

using SharedCamera = std::shared_ptr<Camera>;
using WeakCamera = std::weak_ptr<Camera>;

#endif // CAMERA_H
