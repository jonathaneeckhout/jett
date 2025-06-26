#include "jett/objects/game_object.hpp"

GameObject::GameObject(Game &game) : game_(game)
{
    entity_ = game.createEntity();

    game.getRegistry().emplace<EventsComponent>(entity_);
}

GameObject::~GameObject()
{
    game_.removeEntity(entity_);
}