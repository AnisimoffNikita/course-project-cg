#include "scene.h"

#include <algorithm>

#include "rendercontext.h"

void Scene::add(const SharedSceneObject &child)
{
    _children.push_back(child);
}

//SharedSceneObject Scene::get(int32 tag)
//{
//    shared_ptr<SceneObject> result = nullptr;
//    for (const auto &child : _children)
//        if (child->getTag() == tag)
//            result = child;
//    return result;
//}

//void Scene::remove(int32 tag)
//{
//    auto childIt = find_if(begin(_children), end(_children), [tag](auto child) {
//        return child->getTag() == tag;
//    });

//    if (childIt == end(_children))
//        return;

//    auto child = *childIt;

//    if (child->isCamera())
//    {
//        for (const auto &child : _children)
//            if (child->isCamera())
//            {
//                _camera = static_pointer_cast<Camera>(child);
//                break;
//            }
//    }

//    _children.erase(childIt);
//}


void Scene::setActiveCamera(const SharedSceneObject &child)
{
    bool cameraExist = std::find(_children.begin(), _children.end(), child) != _children.end();
    if (cameraExist && child->isCamera())
    {
        _camera = static_pointer_cast<Camera>(child);
    }
}

weak_ptr<Camera> Scene::getActiveCamera()
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

    Render render;
    render.setCamera(_camera);
    render.setScale(5);
    render.setPixmap(pixmap);

    for (const auto &child : _children)
        child->draw(render);

    return render.getPixmap();
}

