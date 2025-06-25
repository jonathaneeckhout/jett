#pragma once

#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "jett/utils/vector.hpp"

#include "jett/events/key.hpp"
#include "jett/events/mouse.hpp"
#include "jett/events/quit.hpp"

class Controls
{
public:
    enum MouseEventType
    {
        MOUSE_LEFT_BUTTON,
        MOUSE_RIGHT_BUTTON,
        MOUSE_MIDDLE_BUTTON,
        MOUSE_MOVEMENT
    };

    Controls();
    ~Controls();

    void input();

    template <typename EventType, auto Handler>
    void addEventHandler()
    {
        auto sink = dispatcher_.sink<EventType>();
        sink.template connect<Handler>();
    };

    template <typename EventType, auto Handler>
    void removeEventHandler()
    {
        auto sink = dispatcher_.sink<EventType>();
        sink.template disconnect<Handler>();
    };

    void registerKeys(const std::string &name, const std::string &key);
    const std::string getMapping(const std::string &name);
    bool isMapping(const std::string &name, const std::string &key);
    void clearMappings();

    Vector getMousePosition() { return mouse_position_; };
    Vector getMousePressedPosition() { return mouse_pressed_position_; };
    Vector getMouseReleasedPosition() { return mouse_released_position_; };

    bool isMouseButtonPressed(MouseEventType type);

private:
    entt::dispatcher dispatcher_;

    Vector mouse_position_ = Vector();
    Vector mouse_pressed_position_ = Vector();
    Vector mouse_released_position_ = Vector();

    bool left_mouse_button_pressed = false;
    bool right_mouse_button_pressed = false;
    bool middle_mouse_button_pressed = false;

    std::unordered_map<std::string, std::string> key_mappings_;
};