#pragma once

#include <vector>
#include <entt/entt.hpp>

struct ChildrenComponent
{
    std::vector<entt::entity> children;
};
