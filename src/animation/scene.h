#ifndef SCENE_H
#define SCENE_H


#include <memory>
#include <utility>
#include <vector>

#include "sceneobject.h"
#include "camera.h"

#include "src/number.h"

#include <QPixmap>
#include "renderer.h"

using namespace std;

class Scene
{
public:
    Scene() = default;

    virtual ~Scene() = default;

    virtual void add(const SharedSceneObject &child);

    virtual void setActiveCamera(const SharedSceneObject &child);
    virtual WeakCamera getActiveCamera();

    virtual vector<SharedSceneObject> getChildren();

    virtual QPixmap render();
protected:
    vector<SharedSceneObject> _children;
    WeakCamera _camera;
};


#endif // SCENE_H
