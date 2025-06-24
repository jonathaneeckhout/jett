#include "jett/systems/button.hpp"
#include "jett/components/transform.hpp"
#include "jett/components/button.hpp"

void renderButton(GameContext &ctx)
{
    auto view = ctx.registry.view<TransformComponent, ButtonComponent>();
    for (auto entity : view)
    {
        auto [transform, button] = view.get<TransformComponent, ButtonComponent>(entity);

        ctx.renderer.drawRect(transform.position, button.size, button.color);
    }
}