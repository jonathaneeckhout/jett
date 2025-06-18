#pragma once

#include <entt/entt.hpp>
#include <unordered_map>
#include <functional>
#include <cstdint>

struct GameContext
{
    entt::registry &registry;
};

class Game
{
public:
    Game(std::uint32_t update_fps = 60, std::uint32_t render_fps = 60);
    ~Game();

    void run();
    void stop();

    std::uint32_t registerInputSystem(std::function<void(GameContext &)> systemFn) { return registerSystem(systemFn, input_systems_); }
    void unregisterInputSystem(std::uint32_t id) { unregisterSystem(id, input_systems_); }

    std::uint32_t registerUpdateSystem(std::function<void(GameContext &)> systemFn) { return registerSystem(systemFn, update_systems_); }
    void unregisterUpdateSystem(std::uint32_t id) { unregisterSystem(id, update_systems_); }

    std::uint32_t registerRenderSystem(std::function<void(GameContext &)> systemFn) { return registerSystem(systemFn, render_systems_); }
    void unregisterRenderSystem(std::uint32_t id) { unregisterSystem(id, render_systems_); }

private:
    bool running_ = false;

    double ms_per_update_;
    double ms_per_render_;

    entt::registry registry_;

    std::uint32_t system_offset_ = 0;

    std::unordered_map<std::uint32_t, std::function<void(GameContext &)>> input_systems_;
    std::unordered_map<std::uint32_t, std::function<void(GameContext &)>> update_systems_;
    std::unordered_map<std::uint32_t, std::function<void(GameContext &)>> render_systems_;

    void input();
    void update();
    void render();

    std::uint32_t registerSystem(
        std::function<void(GameContext &)> systemFn,
        std::unordered_map<std::uint32_t, std::function<void(GameContext &)>> &map);
    void unregisterSystem(
        std::uint32_t id,
        std::unordered_map<std::uint32_t, std::function<void(GameContext &)>> &systems);
};