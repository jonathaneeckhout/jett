#pragma once

#include <entt/entt.hpp>

#include "jett/core/game.hpp"
#include "jett/components/events.hpp"

class GameObject
{
public:
    GameObject(Game &game);
    virtual ~GameObject();

    const entt::entity &getEntity() { return entity_; };

    template <typename EventType, auto Handler>
    void addEventHandler()
    {
        auto &events = get<EventsComponent>();
        auto sink = events.dispatcher.sink<EventType>();
        sink.template connect<Handler>();
    };

    template <typename EventType, auto Handler>
    void removeEventHandler()
    {
        auto &events = get<EventsComponent>();
        auto sink = events.dispatcher.sink<EventType>();
        sink.template disconnect<Handler>();
    };
    template <typename ComponentType>
    ComponentType &get()
    {
        return game_.getRegistry().get<ComponentType>(entity_);
    }

    bool addChild(entt::entity child);

    bool removeChild(entt::entity child);

protected:
    entt::entity entity_;
    Game &game_;
};