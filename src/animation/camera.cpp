#include "camera.h"

#include "matrixfactory.h"
#include "transformation.h"

Camera::Camera(const Vec3 &position, const Vec3 &lookAt, const Vec3 &up,
               const Mat4 &projection) :
    SceneObject(position),
    lookAt(lookAt),
    up(up),
    projectionMatrix(projection)
{
    updateViewMatrix();
}


void Camera::draw(std::unique_ptr<Renderer> &)
{
    return;
}

void Camera::transform(const Transformation &transformation)
{
    transformation.transform(position);
    updateViewMatrix();
}

bool Camera::isCamera()
{
    return true;
}

bool Camera::isLight()
{
    return false;
}

void Camera::setLookAt(const Vec3 &target)
{
    lookAt = target;
    updateViewMatrix();
}

Vec3 Camera::getEyeVector()
{
    return lookAt - position;
}

Mat4 Camera::getPVMatrix()
{
    return projectionMatrix * viewMatrix;
}

void Camera::updateViewMatrix()
{
    viewMatrix = ViewMatrix::create(position, lookAt, up);
}


void Camera::setPosition(const Vec3 &value)
{
    position = value;
    updateViewMatrix();
}
