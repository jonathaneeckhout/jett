#pragma once

#include <entt/entt.hpp>

#include "jett/objects/game_object.hpp"

class Button : public GameObject
{
public:
    Button(Game &game, Vector position, Vector size);
    ~Button();
};