#ifndef SCENE_H
#define SCENE_H


#include <memory>
#include <utility>
#include <vector>

#include "sceneobject.h"
#include "camera.h"
#include "light.h"

#include "src/number.h"

#include <QPixmap>

class Renderer;

using namespace std;

class Scene
{
public:
    Scene() = default;

    virtual ~Scene() = default;

    virtual void add(const SharedSceneObject &child);

    virtual void setActiveCamera(const SharedSceneObject &child);
    virtual WeakCamera getActiveCamera() const;

    virtual const vector<SharedSceneObject>& getChildren() const;

    virtual void render(std::unique_ptr<Renderer> &renderer);
protected:
    vector<SharedSceneObject> _children;
    WeakCamera _camera;
    vector<WeakLight> lights;
};


#endif // SCENE_H
