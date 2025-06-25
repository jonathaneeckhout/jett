#include "jett/systems/rectangle.hpp"

#include "jett/components/transform.hpp"
#include "jett/components/rectangle.hpp"

void renderRectangle(GameContext &ctx)
{
    auto view = ctx.registry.view<TransformComponent, RectangleComponent>();
    for (auto entity : view)
    {
        auto [transform, rectangle] = view.get<TransformComponent, RectangleComponent>(entity);
        ctx.renderer.drawRect(transform.position, rectangle.size, rectangle.color);
    }
}
