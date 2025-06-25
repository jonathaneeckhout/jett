#pragma once

#include <entt/entt.hpp>

#include "jett/core/game.hpp"

class Button
{
public:
    Button(Game &game, Vector position, Vector size);
    ~Button();

    const entt::entity &getEntity() { return entity_; };

private:
    entt::entity entity_;
    Game &game_;

    std::uint32_t render_button_system_id;
    std::uint32_t handle_button_input_system_id;
};