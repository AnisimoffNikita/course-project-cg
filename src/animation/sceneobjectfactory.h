#ifndef SCENEOBJECTFACTORY_H
#define SCENEOBJECTFACTORY_H

#include "sceneobject.h"
#include "camera.h"
#include "model.h"

class SceneObjectFactory
{
public:
    SceneObjectFactory() = default;

    virtual ~SceneObjectFactory() = default;

    virtual SharedSceneObject create() = 0;
};

//TODO: move to own header
class CameraFactory : public SceneObjectFactory
{
public:
    struct PerspectiveData
    {
        double fovX;
        double fovY;
        double near;
        double far;
    };

public:
    CameraFactory(const Vertex &position, const Vertex &lookAt, const Vertex &up, const PerspectiveData &data);
    //TODO: CameraFactory(const Vertex &position, const Vertex &target, const OrthographicData &data);
    virtual ~CameraFactory() = default;

    virtual SharedSceneObject create() override;

private:
    std::unique_ptr<Camera> camera;
};

class ModelFactory : public SceneObjectFactory
{
public:
    ModelFactory(const Vertex &position, const Mesh &mesh);
    virtual ~ModelFactory() = default;

    virtual SharedSceneObject create() override;
private:
    std::unique_ptr<Model> model;
};

#endif // SCENEOBJECTFACTORY_H
