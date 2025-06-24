#pragma once

#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include <unordered_map>
#include <functional>
#include <cstdint>

#include "jett/core/renderer.hpp"
#include "jett/core/controls.hpp"

struct GameContext
{
    entt::registry &registry;
    Renderer &renderer;
    Controls &controls;
};

class Game
{
public:
    Game(
        const std::string &title = "",
        Vector window_size = {800.0, 600.0},
        std::uint32_t update_fps = 60,
        std::uint32_t render_fps = 60);
    ~Game();
    void run();
    void stop();

    entt::entity createEntity();
    void removeEntity(entt::entity entity);

    entt::registry &getRegistry() { return registry_; };

    std::uint32_t registerInputSystem(std::function<void(GameContext &)> systemFn);
    void unregisterInputSystem(std::uint32_t id);

    std::uint32_t registerUpdateSystem(std::function<void(GameContext &)> systemFn);
    void unregisterUpdateSystem(std::uint32_t id);

    std::uint32_t registerRenderSystem(std::function<void(GameContext &)> systemFn);
    void unregisterRenderSystem(std::uint32_t id);

    Controls &getControls() { return *controls_; }

private:
    bool running_ = false;
    double period_per_update_;
    double period_per_render_;

    entt::registry registry_;

    Renderer *renderer_ = nullptr;

    Controls *controls_ = nullptr;

    struct SystemRefCount
    {
        std::function<void(GameContext &)> systemFn;
        std::uint32_t refCount;
    };

    std::uint32_t system_offset_ = 0;
    std::unordered_map<std::uint32_t, SystemRefCount> input_systems_;
    std::unordered_map<std::uint32_t, SystemRefCount> update_systems_;
    std::unordered_map<std::uint32_t, SystemRefCount> render_systems_;

    void input(GameContext &ctx);
    void update(GameContext &ctx);
    void render(GameContext &ctx);

    std::uint32_t registerSystem(
        std::function<void(GameContext &)> systemFn,
        std::unordered_map<std::uint32_t, SystemRefCount> &map);

    void unregisterSystem(
        std::uint32_t id,
        std::unordered_map<std::uint32_t, SystemRefCount> &map);
};