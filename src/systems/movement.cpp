#include "jett/systems/movement.hpp"

#include "jett/components/transform.hpp"
#include "jett/components/velocity.hpp"
#include "jett/components/children.hpp"

void moveSystem(GameContext &ctx)
{
    auto view = ctx.registry.view<TransformComponent, VelocityComponent, ChildrenComponent>();
    for (auto entity : view)
    {
        auto [transform, velocity, children] = view.get<TransformComponent, VelocityComponent, ChildrenComponent>(entity);

        if (velocity.velocity == Vector(0, 0))
        {
            continue;
        }

        auto delta_position = velocity.velocity * ctx.delta;

        transform.position += delta_position;

        for (auto &child : children.children)
        {
            auto &child_transform = ctx.registry.get<TransformComponent>(child);

            child_transform.position += delta_position;
        }
    }
}