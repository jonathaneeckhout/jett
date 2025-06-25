#pragma once

#include <entt/entt.hpp>

struct ButtonEvent
{
    entt::entity entity;
    bool pressed;
};