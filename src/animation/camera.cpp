#include "camera.h"

#include "matrixfactory.h"
#include "transformation.h"

Camera::Camera(const Vertex &position, const Vertex &lookAt, const Vertex &up,
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

void Camera::setLookAt(const Vertex &target)
{
    lookAt = target;
    updateViewMatrix();
}

Vertex Camera::getEyeVector()
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


void Camera::setPosition(const Vertex &value)
{
    position = value;
    updateViewMatrix();
}
