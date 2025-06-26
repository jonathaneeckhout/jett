#include "jett/objects/game_object.hpp"
#include "jett/components/parent.hpp"
#include "jett/components/children.hpp"

#include "jett/utils/children.hpp"

GameObject::GameObject(Game &game) : game_(game)
{
    entity_ = game.createEntity();

    game.getRegistry().emplace<EventsComponent>(entity_);

    game.getRegistry().emplace<ParentComponent>(entity_);

    game.getRegistry().emplace<ChildrenComponent>(entity_);
}

GameObject::~GameObject()
{
    game_.removeEntity(entity_);
}

bool GameObject::addChild(entt::entity child)
{
    return addChildToParent(game_.getRegistry(), entity_, child);
}

bool GameObject::removeChild(entt::entity child)
{
    return removeChildFromParent(game_.getRegistry(), entity_, child);
}