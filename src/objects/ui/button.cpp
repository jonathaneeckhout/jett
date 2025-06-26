#include "jett/objects/ui/button.hpp"

#include "jett/components/transform.hpp"
#include "jett/components/button.hpp"
#include "jett/components/rectangle.hpp"
#include "jett/components/events.hpp"

#include "jett/systems/button.hpp"
#include "jett/systems/rectangle.hpp"

Button::Button(Game &game, Vector position, Vector size) : GameObject(game)
{
    emplace<TransformComponent>(position);

    emplace<ButtonComponent>(
        BUTTON_IDLE,
        SDL_Color{32, 32, 32, 255},
        SDL_Color{128, 128, 128, 255},
        SDL_Color{196, 196, 196, 255});

    emplace<RectangleComponent>(
        size,
        SDL_Color{32, 32, 32, 255});

    registerInputSystem(handleButtonInputSystem);

    registerRenderSystem(renderRectangleSystem);
}

Button::~Button() {}
