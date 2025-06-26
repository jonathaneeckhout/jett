#pragma once

#include <SDL3/SDL.h>

#include "jett/objects/game_object.hpp"

class Rectangle : public GameObject
{

public:
    Rectangle(Game &game, Vector position, Vector size, SDL_Color color);
    ~Rectangle();

private:
    std::uint32_t movement_system_id;
    std::uint32_t rect_system_id;
};