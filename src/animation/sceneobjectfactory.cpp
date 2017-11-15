#include "sceneobjectfactory.h"

#include "matrixfactory.h"

CameraFactory::CameraFactory(const Vertex &position, const Vertex &lookAt, const Vertex &up, const CameraFactory::PerspectiveData &data)
{
    Mat4 projection = PerspectiveMatrix::create(data.fovX, data.fovY, data.near, data.far);
    camera = std::make_unique<Camera>(position, lookAt, up, projection);
}

SharedSceneObject CameraFactory::create()
{
    return std::move(camera);
}

ModelFactory::ModelFactory(const Vertex &position, const Mesh &mesh)
{
    model = std::make_unique<Model>(position, mesh);
}

SharedSceneObject ModelFactory::create()
{
    return std::move(model);
}
