#pragma once

#include <iostream>

#include "jett/vector.hpp"

enum MouseEventType
{
    MOUSE_LEFT_BUTTON,
    MOUSE_RIGHT_BUTTON,
    MOUSE_MIDDLE_BUTTON,
    MOUSE_MOVEMENT
};

struct KeyEvent
{
    std::string key;
    bool pressed;
};

struct MouseEvent
{
    MouseEventType type;
    bool pressed;
    Vector coordinates;
};