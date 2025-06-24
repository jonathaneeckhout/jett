#include "jett/entities/ui/button.hpp"

#include "jett/components/transform.hpp"
#include "jett/components/button.hpp"

#include "jett/systems/button.hpp"

Button::Button(Game &game, Vector position, Vector size) : game_(game)
{
    entity_ = game.createEntity();

    game.getRegistry().emplace<TransformComponent>(entity_, position);
    game.getRegistry().emplace<ButtonComponent>(entity_, false, SDL_Color{0, 255, 0, 255}, size);

    render_button_system_id = game.registerRenderSystem(renderButton);
}

Button::~Button()
{
    game_.unregisterRenderSystem(render_button_system_id);

    game_.removeEntity(entity_);
}
