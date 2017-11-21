#include "scene.h"

#include <algorithm>

#include "renderer.h"

void Scene::add(const SharedSceneObject &child)
{
    _children.push_back(child);

    if (child->isLight())
    {
        lights.push_back(static_pointer_cast<Light>(child));
    }
}

void Scene::setActiveCamera(const SharedSceneObject &child)
{
    bool cameraExist = std::find(_children.begin(), _children.end(),
                                 child) != _children.end();

    if (cameraExist && child->isCamera())
    {
        _camera = static_pointer_cast<Camera>(child);
    }
}

WeakCamera Scene::getActiveCamera() const
{
    return _camera;
}


const vector<SharedSceneObject> &Scene::getChildren() const
{
    return _children;
}

void Scene::render(std::unique_ptr<Renderer> &renderer)
{
    for (const auto &light : lights)
    {
        if (!light.expired())
        {
            renderer->addLight(light.lock());
        }
    }

    if (_camera.expired())
    {
        return;
    }

    renderer->setCamera(_camera.lock());

    for (const auto &child : _children)
    {
        child->draw(renderer);
    }
}
