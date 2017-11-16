#include "scene.h"

#include <algorithm>

#include "renderer.h"

void Scene::add(const SharedSceneObject &child)
{
    _children.push_back(child);
}

void Scene::setActiveCamera(const SharedSceneObject &child)
{
    bool cameraExist = std::find(_children.begin(), _children.end(), child) != _children.end();
    if (cameraExist && child->isCamera())
    {
        _camera = static_pointer_cast<Camera>(child);
    }
}

WeakCamera Scene::getActiveCamera()
{
    return _camera;
}


vector<SharedSceneObject> Scene::getChildren()
{
    return _children;
}

QPixmap Scene::render()
{
    QPixmap pixmap(960,640);
    pixmap.fill(Qt::white);

    Renderer render;
    render.setCamera(_camera);
    render.setScale(100);
    render.setPixmap(pixmap);

    for (const auto &child : _children)
        child->draw(render);

    return render.getPixmap();
}

