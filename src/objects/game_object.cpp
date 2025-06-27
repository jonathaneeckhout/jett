#include "jett/objects/game_object.hpp"
#include "jett/components/parent.hpp"
#include "jett/components/children.hpp"

#include "jett/utils/children.hpp"

GameObject::GameObject(Game &game) : game_(game)
{
    entity_ = game.createEntity();

    game.addObject(entity_, this);

    emplace<EventsComponent>();

    emplace<ParentComponent>();

    emplace<ChildrenComponent>();
}

GameObject::~GameObject()
{
    unregisterAllInputSystems();
    unregisterAllUpdateSystems();
    unregisterAllRenderSystems();

    game_.removeObject(entity_);

    game_.removeEntity(entity_);
}

void GameObject::queueDelete()
{
    queuedForDeletion_ = true;

    auto &children = game_.getRegistry().get<ChildrenComponent>(entity_);
    for (auto child_entity : children.children)
    {
        auto child = game_.getObject(child_entity);
        child->queueDelete();
    }

    game_.queueForDeletion_(entity_);
}

bool GameObject::addChild(GameObject &child)
{
    return addChildToParent(game_.getRegistry(), entity_, child.getEntity());
}

bool GameObject::removeChild(GameObject &child)
{
    return removeChildFromParent(game_.getRegistry(), entity_, child.getEntity());
}

std::uint32_t GameObject::registerInputSystem(std::function<void(GameContext &)> systemFn)
{
    std::uint32_t system_id = game_.registerInputSystem(systemFn);

    input_systems_.push_back(system_id);

    return system_id;
}

void GameObject::unregisterInputSystem(std::uint32_t id)
{
    game_.unregisterInputSystem(id);

    input_systems_.erase(std::remove(input_systems_.begin(), input_systems_.end(), id), input_systems_.end());
}

void GameObject::unregisterAllInputSystems()
{
    for (auto id : input_systems_)
    {
        game_.unregisterInputSystem(id);
    }
    input_systems_.clear();
}

std::uint32_t GameObject::registerUpdateSystem(std::function<void(GameContext &)> systemFn)
{
    std::uint32_t system_id = game_.registerUpdateSystem(systemFn);

    update_systems_.push_back(system_id);

    return system_id;
}

void GameObject::unregisterUpdateSystem(std::uint32_t id)
{
    game_.unregisterUpdateSystem(id);

    update_systems_.erase(std::remove(update_systems_.begin(), update_systems_.end(), id), update_systems_.end());
}

void GameObject::unregisterAllUpdateSystems()
{
    for (auto id : update_systems_)
    {
        game_.unregisterUpdateSystem(id);
    }
    update_systems_.clear();
}

std::uint32_t GameObject::registerRenderSystem(std::function<void(GameContext &)> systemFn)
{
    std::uint32_t system_id = game_.registerRenderSystem(systemFn);

    render_systems_.push_back(system_id);

    return system_id;
}

void GameObject::unregisterRenderSystem(std::uint32_t id)
{
    game_.unregisterRenderSystem(id);

    render_systems_.erase(std::remove(render_systems_.begin(), render_systems_.end(), id), render_systems_.end());
}

void GameObject::unregisterAllRenderSystems()
{
    for (auto id : render_systems_)
    {
        game_.unregisterRenderSystem(id);
    }
    render_systems_.clear();
}