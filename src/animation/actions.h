#ifndef ACTIONS_H
#define ACTIONS_H

#include "sceneobject.h"
#include "src/math/vec3.h"

using namespace std;

class Action
{
public:
    Action(float duration, weak_ptr<SceneObject> object);
    virtual ~Action() = default;

    virtual bool update(float delta) = 0;
protected:
    float duration;
    float time;
    weak_ptr<SceneObject> object;
};

class RepeatMoveAction : public Action
{
public:
    RepeatMoveAction(float duration, weak_ptr<SceneObject> object,
                     const Vec3 &finish);

    virtual bool update(float delta);
protected:
    Vec3 start;
    Vec3 diff;
};

#endif // ACTIONS_H
