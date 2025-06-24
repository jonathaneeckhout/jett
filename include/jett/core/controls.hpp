#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "jett/vector.hpp"
#include "jett/events/events.hpp"

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

    int addQuitHandler(void (*handler)());
    void removeQuitHandler(int id);

    int addKeyHandler(void (*handler)(std::string key, bool pressed));
    void removeKeyHandler(int id);

    int addMouseHandler(void (*handler)(MouseEventType event_type, bool pressed, Vector mouse_position));
    void removeMouseHandler(int id);

    void registerKeys(const std::string &name, const std::string &key);
    const std::string getMapping(const std::string &name);
    bool isMapping(const std::string &name, const std::string &key);
    void clearMappings();

private:
    Events events_;

    std::unordered_map<std::string, std::string> key_mappings_;
};