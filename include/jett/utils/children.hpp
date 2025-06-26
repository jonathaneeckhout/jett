#pragma once

#include <entt/entt.hpp>
#include "jett/components/children.hpp"

void addChild(entt::registry &registry, entt::entity parent, entt::entity child);

bool removeChild(entt::registry &registry, entt::entity parent, entt::entity child);
