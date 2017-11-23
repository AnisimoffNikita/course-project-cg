#include "sceneobjectfactory.h"

#include "matrixfactory.h"

CameraFactory::CameraFactory(const Vec3 &position, const Vec3 &lookAt,
                             const Vec3 &up, const CameraFactory::PerspectiveData &data)
{
    Mat4 projection = PerspectiveMatrix::create(data.fovX, data.fovY, data.near,
                      data.far);
    camera = std::make_unique<Camera>(position, lookAt, up, projection);
}

SharedSceneObject CameraFactory::create()
{
    return std::move(camera);
}

ModelFactory::ModelFactory(const Vec3 &position, const Mesh &mesh)
{
    model = std::make_unique<Model>(position, mesh);
}

SharedSceneObject ModelFactory::create()
{
    return std::move(model);
}

AmbientLightFactory::AmbientLightFactory(float intensity)
{
    light = std::make_unique<AmbientLight>(intensity);
}

SharedSceneObject AmbientLightFactory::create()
{
    return std::move(light);
}

PointLightFactory::PointLightFactory(const Vec3 &position, float intensity)
{
    light = std::make_unique<PointLight>(position, intensity);
}

SharedSceneObject PointLightFactory::create()
{
    return std::move(light);
}
