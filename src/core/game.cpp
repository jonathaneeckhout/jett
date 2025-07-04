#include <chrono>
#include <thread>
#include <libassert/assert.hpp>
#include <stdexcept>
#include <vector>

#include "jett/core/game.hpp"
#include "jett/objects/game_object.hpp"
#include "jett/systems/events.hpp"

Game::Game(
    const std::string &title,
    Vector window_size,
    std::uint32_t update_fps,
    std::uint32_t render_fps)
{
    if (update_fps == 0)
    {
        throw std::invalid_argument("Update FPS must be greater than 0.");
    }

    if (render_fps == 0)
    {
        throw std::invalid_argument("Render FPS must be greater than 0.");
    }

    period_per_update_ = 1.0 / update_fps;
    period_per_render_ = render_fps > 0 ? 1.0 / render_fps : 0;

    renderer_ = new Renderer(title, window_size);

    controls_ = new Controls();
}

Game::~Game()
{
    cleanAllObjects();

    delete controls_;
    controls_ = nullptr;

    delete renderer_;
    renderer_ = nullptr;
}

void Game::run()
{
    using clock = std::chrono::high_resolution_clock;
    using namespace std::chrono;

    running_ = true;
    double lag = 0.0;
    auto previous_time = clock::now();

    while (running_)
    {
        auto current_time = clock::now();
        duration<double> elapsed = current_time - previous_time;
        previous_time = current_time;
        lag += elapsed.count();

        GameContext ctx = {
            .registry = registry_,
            .dispatcher = dispatcher_,
            .renderer = *renderer_,
            .controls = *controls_,
            .delta = period_per_update_};

        input(ctx);

        while (lag >= period_per_update_)
        {
            update(ctx);
            lag -= period_per_update_;
        }

        render(ctx);

        auto frame_end = clock::now();
        duration<double> frame_duration = frame_end - current_time;

        double frame_time = frame_duration.count();
        if (frame_time < period_per_render_)
        {
            auto sleep_time = duration<double>(period_per_render_ - frame_time);
            std::this_thread::sleep_for(sleep_time);
        }
    }
}

void Game::stop()
{
    running_ = false;
}

void Game::input(GameContext &ctx)
{
    controls_->input();

    for (auto &[id, systemRefCount] : input_systems_)
    {
        systemRefCount.systemFn(ctx);
    }
}

void Game::update(GameContext &ctx)
{
    sendEventsSystem(ctx);

    for (auto &[id, systemRefCount] : update_systems_)
    {
        systemRefCount.systemFn(ctx);
    }

    deleteQueuedObjects();
}

void Game::render(GameContext &ctx)
{
    renderer_->clear();

    for (auto &[id, systemRefCount] : render_systems_)
    {
        systemRefCount.systemFn(ctx);
    }

    renderer_->present();
}

entt::entity Game::createEntity()
{
    return registry_.create();
}

void Game::removeEntity(entt::entity entity)
{
    if (registry_.valid(entity))
    {
        registry_.destroy(entity);
    }
}

void Game::addObject(entt::entity entity, GameObject *object)
{
    objects_[entity] = object;
}

void Game::removeObject(entt::entity entity)
{
    objects_.erase(entity);
}

GameObject *Game::getObject(entt::entity entity)
{
    auto it = objects_.find(entity);
    if (it == objects_.end())
    {
        return nullptr;
    }

    return it->second;
}

void Game::queueForDeletion_(entt::entity entity)
{
    to_be_deleted_objects_.push_back(entity);
}

void Game::deleteQueuedObjects()
{
    for (auto entry : to_be_deleted_objects_)
    {
        auto obj = getObject(entry);
        if (obj != nullptr)
        {
            delete obj;
        }
    }

    to_be_deleted_objects_.clear();
}

void Game::cleanAllObjects()
{
    std::vector<GameObject *> to_be_deleted;

    for (auto &entry : objects_)
    {
        to_be_deleted.push_back(entry.second);
    }

    for (auto obj : to_be_deleted)
    {
        delete obj;
    }

    objects_.clear();
}

std::uint32_t Game::registerSystem(
    std::function<void(GameContext &)> systemFn,
    std::unordered_map<std::uint32_t, SystemRefCount> &map)
{
    for (auto &entry : map)
    {
        if (entry.second.systemFn.target_type() == systemFn.target_type())
        {
            entry.second.refCount++;
            return entry.first;
        }
    }

    std::uint32_t id = system_offset_++;
    map[id] = {systemFn, 1};
    return id;
}

void Game::unregisterSystem(
    std::uint32_t id,
    std::unordered_map<std::uint32_t, SystemRefCount> &map)
{

    auto it = map.find(id);
    if (it != map.end())
    {
        it->second.refCount--;
        if (it->second.refCount == 0)
        {
            map.erase(it);
        }
    }
}

std::uint32_t Game::registerInputSystem(std::function<void(GameContext &)> systemFn)
{
    return registerSystem(systemFn, input_systems_);
}

void Game::unregisterInputSystem(std::uint32_t id)
{
    unregisterSystem(id, input_systems_);
}

std::uint32_t Game::registerUpdateSystem(std::function<void(GameContext &)> systemFn)
{
    return registerSystem(systemFn, update_systems_);
}

void Game::unregisterUpdateSystem(std::uint32_t id)
{
    unregisterSystem(id, update_systems_);
}

std::uint32_t Game::registerRenderSystem(std::function<void(GameContext &)> systemFn)
{
    return registerSystem(systemFn, render_systems_);
}

void Game::unregisterRenderSystem(std::uint32_t id)
{
    unregisterSystem(id, render_systems_);
}