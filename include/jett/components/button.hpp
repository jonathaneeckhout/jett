#pragma once

#include <SDL3/SDL.h>
#include "jett/vector.hpp"

struct ButtonComponent
{
    bool is_pressed = false;
    SDL_Color color;
    Vector size;
};
