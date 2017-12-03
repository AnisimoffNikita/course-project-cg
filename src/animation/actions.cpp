#include "actions.h"

Action::Action(float duration, weak_ptr<SceneObject> object)
    : duration(duration)
    , time(0)
    , object(object)
{
}

RepeatMoveAction::RepeatMoveAction(float duration, weak_ptr<SceneObject> object,
                                   const Vec3 &finish)
    : Action(duration, object)
{
    if (!object.expired())
    {
        start = object.lock()->getPosition();
        diff = finish - start;
    }
}

bool RepeatMoveAction::update(float delta)
{
    if (object.expired())
    {
        return true;
    }

    auto work = object.lock();
    time += delta;

    if (time >= duration)
    {
        time -= duration;
    }

    float fraction = time / duration;
    work->setPosition(start + diff * fraction);
    return false;
}
