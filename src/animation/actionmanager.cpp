#include "actionmanager.h"

ActionManager::ActionManager()
{
}

void ActionManager::add(unique_ptr<Action> &&action)
{
    actions.push_back(std::move(action));
}

void ActionManager::update(float delta)
{
    //TODO: check for delete
    for (auto &action : actions)
    {
        action->update(delta);
    }
}
