#pragma once

#include <entt/entt.hpp>

#include "jett/utils/vector.hpp"

struct ParentComponent
{
    entt::entity parent;
    Vector offset;
};