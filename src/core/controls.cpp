#include "jett/core/controls.hpp"

Controls::Controls() {}

Controls::~Controls() {}

void Controls::input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            dispatcher_.trigger(QuitEvent{});
            break;
        case SDL_EVENT_KEY_DOWN:
        {
            SDL_Keycode key_code = event.key.key;

            std::string key_name = SDL_GetKeyName(key_code);

            dispatcher_.trigger(KeyEvent{key_name, true});
        }
        break;
        case SDL_EVENT_KEY_UP:
        {
            SDL_Keycode key_code = event.key.key;

            std::string key_name = SDL_GetKeyName(key_code);

            dispatcher_.trigger(KeyEvent{key_name, false});
        }
        break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            mouse_position_ = Vector(event.button.x, event.button.y);
            mouse_pressed_position_ = mouse_position_;

            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                left_mouse_button_pressed = true;

                dispatcher_.trigger(MouseLeftEvent{mouse_position_, true});
                break;
            case SDL_BUTTON_RIGHT:
                right_mouse_button_pressed = true;

                dispatcher_.trigger(MouseRightEvent{mouse_position_, true});
            case SDL_BUTTON_MIDDLE:
                middle_mouse_button_pressed = true;

                dispatcher_.trigger(MouseMiddleEvent{mouse_position_, true});
                break;
            default:
                break;
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            mouse_position_ = Vector(event.button.x, event.button.y);
            mouse_released_position_ = mouse_position_;

            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                left_mouse_button_pressed = false;

                dispatcher_.trigger(MouseLeftEvent{mouse_position_, false});
                break;
            case SDL_BUTTON_RIGHT:
                right_mouse_button_pressed = false;

                dispatcher_.trigger(MouseRightEvent{mouse_position_, false});
                break;
            case SDL_BUTTON_MIDDLE:
                middle_mouse_button_pressed = false;

                dispatcher_.trigger(MouseMiddleEvent{mouse_position_, false});
                break;
            default:
                break;
            }
            break;
        case SDL_EVENT_MOUSE_MOTION:
            mouse_position_ = Vector(event.motion.x, event.motion.y);

            dispatcher_.trigger(MouseMovementEvent{mouse_position_});
            break;
        default:
            break;
        }
    }
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

bool Controls::isMouseButtonPressed(MouseEventType type)
{
    switch (type)
    {
    case MOUSE_LEFT_BUTTON:
        return left_mouse_button_pressed;
        break;
    case MOUSE_RIGHT_BUTTON:
        return right_mouse_button_pressed;
        break;
    case MOUSE_MIDDLE_BUTTON:
        return middle_mouse_button_pressed;
        break;
    default:
        return false;
        break;
    }
}