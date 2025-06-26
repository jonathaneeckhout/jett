#include "jett/objects/dynamic/rectangle.hpp"

#include "jett/components/transform.hpp"
#include "jett/components/velocity.hpp"
#include "jett/components/rectangle.hpp"

#include "jett/systems/movement.hpp"
#include "jett/systems/rectangle.hpp"

Rectangle::Rectangle(Game &game, Vector position, Vector size, SDL_Color color) : GameObject(game)
{
    emplace<TransformComponent>(position);

    emplace<VelocityComponent>(Vector());

    emplace<RectangleComponent>(size, color);

    registerUpdateSystem(moveSystem);

    registerRenderSystem(renderRectangleSystem);
}

Rectangle::~Rectangle() {}