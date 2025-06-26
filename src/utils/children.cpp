#include "jett/utils/children.hpp"

bool addChildToParent(entt::registry &registry, entt::entity parent, entt::entity child)
{
    if (!registry.all_of<ChildrenComponent>(parent))
    {
        return false;
    }

    auto &children = registry.get<ChildrenComponent>(parent);
    children.children.push_back(child);

    return true;
}

bool removeChildFromParent(entt::registry &registry, entt::entity parent, entt::entity child)
{
    if (!registry.all_of<ChildrenComponent>(parent))
    {
        return false;
    }

    auto &children = registry.get<ChildrenComponent>(parent);
    auto it = std::find(children.children.begin(), children.children.end(), child);
    if (it != children.children.end())
    {
        children.children.erase(it);
        return true;
    }

    return false;
}