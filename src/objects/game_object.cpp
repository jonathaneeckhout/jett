#include "jett/objects/game_object.hpp"
#include "jett/components/parent.hpp"
#include "jett/components/children.hpp"

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