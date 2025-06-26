#include "jett/systems/movement.hpp"

#include "jett/components/transform.hpp"
#include "jett/components/velocity.hpp"
#include "jett/components/children.hpp"

static void updatePositionRecursively(entt::registry &registry, entt::entity entity, const Vector &delta_position)
{
    if (registry.all_of<TransformComponent>(entity))
    {
        auto &transform = registry.get<TransformComponent>(entity);
        transform.position += delta_position;
    }

    if (registry.all_of<ChildrenComponent>(entity))
    {
        auto &children = registry.get<ChildrenComponent>(entity);
        for (auto &child : children.children)
        {
            updatePositionRecursively(registry, child, delta_position);
        }
    }
}

void moveSystem(GameContext &ctx)
{
    auto view = ctx.registry.view<TransformComponent, VelocityComponent, ChildrenComponent>();
    for (auto entity : view)
    {
        auto [transform, velocity, children] = view.get<TransformComponent, VelocityComponent, ChildrenComponent>(entity);

        if (velocity.velocity == Vector{0, 0})
        {
            continue;
        }

        auto delta_position = velocity.velocity * ctx.delta;

        updatePositionRecursively(ctx.registry, entity, delta_position);
    }
}