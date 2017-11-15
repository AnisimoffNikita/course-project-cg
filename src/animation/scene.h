#ifndef SCENE_H
#define SCENE_H


#include <memory>
#include <utility>
#include <vector>

#include "sceneobject.h"
#include "camera.h"

#include "src/number.h"

#include <QPixmap>

using namespace std;

class Scene
{
public:
    Scene() = default;

    virtual ~Scene() = default;

    virtual void add(const SharedSceneObject &child);
//    virtual SharedSceneObject get(int32 tag);
//    virtual void remove(int32 tag);

    virtual void setActiveCamera(const SharedSceneObject &child);
    virtual weak_ptr< Camera > getActiveCamera();

    virtual vector< SharedSceneObject> getChildren();

    virtual QPixmap render();



protected:
    vector< SharedSceneObject> _children;
    weak_ptr< Camera > _camera;
};


#endif // SCENE_H
