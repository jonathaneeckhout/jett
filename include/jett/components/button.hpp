#pragma once

#include <SDL3/SDL.h>
#include "jett/utils/vector.hpp"

enum ButtonState
{
    BUTTON_IDLE,
    BUTTON_SELECTED,
    BUTTON_PRESSED
};

struct ButtonComponent
{
    ButtonState state;
    SDL_Color idle_color;
    SDL_Color selected_color;
    SDL_Color pressed_color;
};
