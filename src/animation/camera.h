#ifndef CAMERA_H
#define CAMERA_H

#include "sceneobject.h"
#include "src/math/matrix.h"

class Camera : public SceneObject
{
public:
    Camera(const Vec3 &position, const Vec3 &lookAt, const Vec3 &up,
           const Mat4 &projection);

    virtual void draw(std::unique_ptr<Renderer> &) override;
    virtual void transform(Transformation &transformation) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;

    virtual void setPosition(const Vec3 &value) override;

    virtual void setLookAt(const Vec3 &target);
    virtual Vec3 getEyeVector();
    virtual Mat4 getPVMatrix();
    virtual const Mat4 &getPMatrix() const;
    virtual const Mat4 &getVMatrix() const;

protected:
    void updateViewMatrix();

    Vec3 lookAt;
    Vec3 up;
    Mat4 viewMatrix;
    Mat4 projectionMatrix;

};

using SharedCamera = std::shared_ptr<Camera>;
using WeakCamera = std::weak_ptr<Camera>;

#endif // CAMERA_H
