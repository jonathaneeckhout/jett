#include "jett/systems/events.hpp"

#include "jett/components/events.hpp"

void sendEvents(GameContext &ctx)
{
    auto view = ctx.registry.view<EventsComponent>();
    for (auto entity : view)
    {
        auto &event = view.get<EventsComponent>(entity);
        event.dispatcher.update();
    }
}
