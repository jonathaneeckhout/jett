#include <chrono>
#include <thread>
#include <libassert/assert.hpp>

#include "jett/core/game.hpp"

Game::Game(std::uint32_t update_fps, std::uint32_t render_fps)
{
    DEBUG_ASSERT(update_fps > 0, "Update_fps is 0 which is invalid");

    if (render_fps > 0)
    {
        ms_per_render_ = 1 / render_fps;
    }
    else
    {
        ms_per_render_ = 0;
    }
}

Game::~Game() = default;

void Game::run()
{
    using clock = std::chrono::high_resolution_clock;

    running_ = true;

    while (running_)
    {
        auto frameStart = clock::now();

        input();

        double lag = 0.0;
        while (lag >= ms_per_update_)
        {
            update();
            lag -= ms_per_update_;
        }

        render();

        auto frameEnd = clock::now();
        std::chrono::duration<double> elapsed = frameEnd - frameStart;
        double frameTime = elapsed.count();

        if (frameTime < ms_per_render_)
        {
            auto sleepTime = std::chrono::duration<double>(ms_per_render_ - frameTime);
            std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(sleepTime));
        }
    }
}

void Game::stop()
{
    running_ = false;
}

void Game::input()
{
    GameContext ctx = {.registry = registry_};

    for (auto &[id, systemFn] : input_systems_)
    {
        systemFn(ctx);
    }
}

void Game::update()
{
    GameContext ctx = {.registry = registry_};

    for (auto &[id, systemFn] : update_systems_)
    {
        systemFn(ctx);
    }
}

void Game::render()
{
    GameContext ctx = {.registry = registry_};

    for (auto &[id, systemFn] : render_systems_)
    {
        systemFn(ctx);
    }
}

std::uint32_t Game::registerSystem(
    std::function<void(GameContext &)> systemFn,
    std::unordered_map<std::uint32_t, std::function<void(GameContext &)>> &systems)
{
    std::uint32_t id = system_offset_++;
    systems[id] = std::move(systemFn);
    return id;
}

void Game::unregisterSystem(
    std::uint32_t id,
    std::unordered_map<std::uint32_t, std::function<void(GameContext &)>> &systems)
{
    systems.erase(id);
}