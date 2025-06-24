#include "jett/core/controls.hpp"

Controls::Controls()
{
    events_.createEvent<>("onQuit");
    events_.createEvent<std::string, bool>("onKey");
    events_.createEvent<MouseEventType, bool, Vector>("onMouse");
}

Controls::~Controls() {}

void Controls::input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            events_.trigger("onQuit");
            break;
        case SDL_EVENT_KEY_DOWN:
        {
            SDL_Keycode key_code = event.key.key;

            std::string key_name = SDL_GetKeyName(key_code);

            events_.trigger("onKey", key_name, true);
        }
        break;
        case SDL_EVENT_KEY_UP:
        {
            SDL_Keycode key_code = event.key.key;

            std::string key_name = SDL_GetKeyName(key_code);

            events_.trigger("onKey", key_name, false);
        }
        break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                events_.trigger("onMouse", MOUSE_LEFT_BUTTON, true, Vector(event.button.x, event.button.y));
                break;
            case SDL_BUTTON_RIGHT:
                events_.trigger("onMouse", MOUSE_RIGHT_BUTTON, true, Vector(event.button.x, event.button.y));
            case SDL_BUTTON_MIDDLE:
                events_.trigger("onMouse", MOUSE_MIDDLE_BUTTON, true, Vector(event.button.x, event.button.y));
                break;
            default:
                break;
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                events_.trigger("onMouse", MOUSE_LEFT_BUTTON, false, Vector(event.button.x, event.button.y));
                break;
            case SDL_BUTTON_RIGHT:
                events_.trigger("onMouse", MOUSE_RIGHT_BUTTON, false, Vector(event.button.x, event.button.y));
                break;
            case SDL_BUTTON_MIDDLE:
                events_.trigger("onMouse", MOUSE_MIDDLE_BUTTON, false, Vector(event.button.x, event.button.y));
                break;
            default:
                break;
            }
            break;
        case SDL_EVENT_MOUSE_MOTION:
            events_.trigger("onMouse", MOUSE_MOVEMENT, false, Vector(event.motion.x, event.motion.y));
            break;
        default:
            break;
        }
    }

    events_.processAll();
}

int Controls::addQuitHandler(void (*handler)())
{
    return events_.addHandler<>("onQuit", handler);
}

void Controls::removeQuitHandler(int id)
{
    events_.removeHandler("onQuit", id);
}

int Controls::addKeyHandler(void (*handler)(std::string key, bool pressed))
{
    return events_.addHandler<std::string, bool>("onKey", handler);
}

void Controls::removeKeyHandler(int id)
{
    events_.removeHandler("onKey", id);
}

int Controls::addMouseHandler(void (*handler)(MouseEventType event_type, bool pressed, Vector mouse_position))
{
    return events_.addHandler<MouseEventType, bool, Vector>("onMouse", handler);
}

void Controls::removeMouseHandler(int id)
{
    events_.removeHandler("onMouse", id);
}

void Controls::registerKeys(const std::string &name, const std::string &key)
{
    key_mappings_[name] = key;
}

const std::string Controls::getMapping(const std::string &name)
{
    auto mapping = key_mappings_.find(name);
    if (mapping == key_mappings_.end())
    {
        return "";
    }

    return mapping->second;
}

bool Controls::isMapping(const std::string &name, const std::string &key)
{
    auto mapping = getMapping(name);
    if (mapping == "")
    {
        return false;
    }

    return key == mapping;
}

void Controls::clearMappings()
{
    key_mappings_.clear();
}