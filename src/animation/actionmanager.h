#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include "sceneobject.h"
#include "actions.h"

using namespace std;

class ActionManager
{
public:
    ActionManager();
    virtual ~ActionManager() = default;

    void add(unique_ptr<Action> &&action);

    void update(float delta);

private:
    vector<unique_ptr<Action>> actions;
};

#endif // ACTIONMANAGER_H
