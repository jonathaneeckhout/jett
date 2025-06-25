#include <SDL3/SDL.h>
#include <entt/entt.hpp>

#include "jett/systems/button.hpp"
#include "jett/components/transform.hpp"
#include "jett/components/button.hpp"
#include "jett/components/rectangle.hpp"
#include "jett/components/events.hpp"
#include "jett/events/button.hpp"
#include "jett/utils/collision.hpp"

void handleButtonInput(GameContext &ctx)
{
    auto view = ctx.registry.view<TransformComponent,
                                  ButtonComponent,
                                  RectangleComponent,
                                  EventsComponent>();
    for (auto entity : view)
    {
        auto [transform, button, rectangle, events] = view.get<TransformComponent,
                                                       ButtonComponent,
                                                       RectangleComponent,
                                                       EventsComponent>(entity);

        if (ctx.controls.isMouseButtonPressed(Controls::MOUSE_LEFT_BUTTON) &&
            pointCollidesWithRect(ctx.controls.getMousePressedPosition(), transform.position, rectangle.size))
        {
            if (button.state != BUTTON_PRESSED)
            {
                events.dispatcher.trigger(ButtonEvent{entity, true});
                button.state = BUTTON_PRESSED;
                rectangle.color = button.pressed_color;
            }
        }
        else if (pointCollidesWithRect(ctx.controls.getMousePosition(), transform.position, rectangle.size))
        {

            button.state = BUTTON_SELECTED;
            rectangle.color = button.selected_color;
        }
        else
        {
            button.state = BUTTON_IDLE;
            rectangle.color = button.idle_color;
        }
    }
}
