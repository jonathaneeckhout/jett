#pragma once

#include <entt/entt.hpp>
#include "jett/components/children.hpp"

bool addChildToParent(entt::registry &registry, entt::entity parent, entt::entity child);

bool removeChildFromParent(entt::registry &registry, entt::entity parent, entt::entity child);
