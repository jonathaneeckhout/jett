#include "jett/objects/dynamic/rectangle.hpp"

#include "jett/components/transform.hpp"
#include "jett/components/velocity.hpp"
#include "jett/components/rectangle.hpp"

#include "jett/systems/movement.hpp"
#include "jett/systems/rectangle.hpp"

Rectangle::Rectangle(Game &game, Vector position, Vector size, SDL_Color color) : GameObject(game)
{
    game.getRegistry().emplace<TransformComponent>(entity_, position);

    game.getRegistry().emplace<VelocityComponent>(entity_, Vector());

    game.getRegistry().emplace<RectangleComponent>(entity_, size, color);

    movement_system_id = game.registerUpdateSystem(moveSystem);

    rect_system_id = game.registerRenderSystem(renderRectangleSystem);
}

Rectangle::~Rectangle()
{
    game_.unregisterUpdateSystem(movement_system_id);

    game_.unregisterRenderSystem(rect_system_id);
}