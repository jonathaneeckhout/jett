#pragma once

#include <entt/entt.hpp>
#include <vector>

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

    template <typename ComponentType, typename... Args>
    decltype(auto) emplace(Args &&...args)
    {
        return game_.getRegistry().emplace<ComponentType>(entity_, std::forward<Args>(args)...);
    }

    template <typename ComponentType>
    ComponentType &get()
    {
        return game_.getRegistry().get<ComponentType>(entity_);
    }

    bool addChild(entt::entity child);
    bool removeChild(entt::entity child);

    std::uint32_t registerInputSystem(std::function<void(GameContext &)> systemFn);
    void unregisterInputSystem(std::uint32_t id);
    void unregisterAllInputSystems();

    std::uint32_t registerUpdateSystem(std::function<void(GameContext &)> systemFn);
    void unregisterUpdateSystem(std::uint32_t id);
    void unregisterAllUpdateSystems();

    std::uint32_t registerRenderSystem(std::function<void(GameContext &)> systemFn);
    void unregisterRenderSystem(std::uint32_t id);
    void unregisterAllRenderSystems();

protected:
    entt::entity entity_;
    Game &game_;

    std::vector<std::uint32_t> input_systems_;
    std::vector<std::uint32_t> update_systems_;
    std::vector<std::uint32_t> render_systems_;
};