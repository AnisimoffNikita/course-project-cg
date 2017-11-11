#ifndef CAMERA_H
#define CAMERA_H

#include "sceneobject.h"

class Camera : public SceneObject
{
public:
    Camera();

    virtual void draw(const RenderContext &render) override;
    virtual void transform(const Transformation &transformation) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;

    virtual void setLookAt(const Vertex &tagret);
    virtual Mat4 getPVMatrix();

protected:
    void updateViewMatrix();

    Mat4 _viewMatrix;
    Mat4 _projectionMatrix;

    Vertex _lookAt;
};

#endif // CAMERA_H
