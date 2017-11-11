#include "scene.h"

#include <algorithm>

void Scene::add(const SharedSceneObject &child)
{
    _children.push_back(child);
}

SharedSceneObject Scene::get(int32 tag)
{
    shared_ptr<SceneObject> result = nullptr;
    for (const auto &child : _children)
        if (child->getTag() == tag)
            result = child;
    return result;
}

void Scene::remove(int32 tag)
{
    auto childIt = find_if(begin(_children), end(_children), [tag](auto child) {
        return child->getTag() == tag;
    });

    if (childIt == end(_children))
        return;

    auto child = *childIt;

    if (child->isCamera())
    {
        for (const auto &child : _children)
            if (child->isCamera())
            {
                _camera = static_pointer_cast<Camera>(child);
                break;
            }
    }

    _children.erase(childIt);
}

void Scene::setActiveCamera(int32 tag)
{
    for (const auto &child : _children)
        if (child->isCamera() && child->getTag() == tag)
        {
            _camera = static_pointer_cast<Camera>(child);
            break;
        }
}

vector<SharedSceneObject> Scene::getChildren()
{
    return _children;
}

void Scene::draw(const RenderContext &render)
{

}
