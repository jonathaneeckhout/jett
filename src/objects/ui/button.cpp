#include "jett/objects/ui/button.hpp"

#include "jett/components/transform.hpp"
#include "jett/components/button.hpp"
#include "jett/components/rectangle.hpp"
#include "jett/components/events.hpp"

#include "jett/systems/button.hpp"
#include "jett/systems/rectangle.hpp"

Button::Button(Game &game, Vector position, Vector size) : GameObject(game)
{
    game.getRegistry().emplace<TransformComponent>(entity_, position);

    game.getRegistry().emplace<ButtonComponent>(
        entity_,
        BUTTON_IDLE,
        SDL_Color{32, 32, 32, 255},
        SDL_Color{128, 128, 128, 255},
        SDL_Color{196, 196, 196, 255});

    game.getRegistry().emplace<RectangleComponent>(
        entity_,
        size,
        SDL_Color{32, 32, 32, 255});

    handle_button_input_system_id = game.registerInputSystem(handleButtonInput);

    render_button_system_id = game.registerRenderSystem(renderRectangle);
}

Button::~Button()
{
    game_.unregisterRenderSystem(render_button_system_id);

    game_.unregisterRenderSystem(handle_button_input_system_id);

    game_.removeEntity(entity_);
}
