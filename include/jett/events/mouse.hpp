#pragma once

#include "jett/utils/vector.hpp"

struct MouseLeftEvent
{
    Vector position;
    bool pressed;
};

struct MouseRightEvent
{
    Vector position;
    bool pressed;
};

struct MouseMiddleEvent
{
    Vector position;
    bool pressed;
};

struct MouseMovementEvent
{
    Vector position;
};