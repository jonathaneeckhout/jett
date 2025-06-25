#pragma once

#include <SDL3/SDL.h>

#include "jett/utils/vector.hpp"

struct RectangleComponent
{
    Vector size;
    SDL_Color color;
};