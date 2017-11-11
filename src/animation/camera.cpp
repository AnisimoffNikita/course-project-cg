#include "camera.h"

#include "matrixfactory.h"

Camera::Camera()
{
    _projectionMatrix = PerspectiveMatrix::create(90,0.75,0.01,100);
    _viewMatrix = ViewMatrix::create(Vertex(),Vertex(),Vertex(0,1,0));
}


void Camera::draw(const RenderContext &render)
{
}

void Camera::transform(const Transformation &transformation)
{
}

bool Camera::isCamera()
{
    return true;
}

bool Camera::isLight()
{
    return false;
}

void Camera::setLookAt(const Vertex &tagret)
{
    _lookAt = target;
    updateViewMatrix();
}

Mat4 Camera::getPVMatrix()
{
    return _projectionMatrix*_viewMatrix;
}

void Camera::updateViewMatrix()
{
    _viewMatrix = ViewMatrix::create(_position,_lookAt,Vertex(0,1,0));
}
