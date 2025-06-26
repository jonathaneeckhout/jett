#pragma once

#include <entt/entt.hpp>

#include "jett/objects/game_object.hpp"

class Button : public GameObject
{
public:
    Button(Game &game, Vector position, Vector size);
    ~Button();

private:
    std::uint32_t render_button_system_id;
    std::uint32_t handle_button_input_system_id;
};