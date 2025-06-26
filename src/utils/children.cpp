#include "jett/utils/children.hpp"

void addChild(entt::registry &registry, entt::entity parent, entt::entity child)
{
    if (registry.all_of<ChildrenComponent>(parent))
    {
        auto &children = registry.get<ChildrenComponent>(parent);
        children.children.push_back(child);
    }
}

bool removeChild(entt::registry &registry, entt::entity parent, entt::entity child)
{
    if (registry.all_of<ChildrenComponent>(parent))
    {
        auto &children = registry.get<ChildrenComponent>(parent);
        auto it = std::find(children.children.begin(), children.children.end(), child);
        if (it != children.children.end())
        {
            children.children.erase(it);
            return true;
        }
    }
    return false;
}