#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "jett/events/event.hpp"

class Events
{
public:
    template <typename... Args>
    void createEvent(const std::string &name)
    {
        if (events_.find(name) != events_.end())
        {
            throw std::runtime_error("Event already exists: " + name);
        }

        events_[name] = std::make_unique<Event<Args...>>(name);
    }

    void deleteEvent(const std::string &name)
    {
        events_.erase(name);
    }

    template <typename... Args>
    int addHandler(const std::string &name, void (*handler)(Args...))
    {
        EventBase *base_event = getEvent(name);

        Event<Args...> *event = dynamic_cast<Event<Args...> *>(base_event);
        if (event == nullptr)
        {
            throw std::runtime_error("Handler type mismatch for event: " + name);
        }

        return event->addHandler(std::move(handler));
    }

    void removeHandler(const std::string &name, int handler_id)
    {
        EventBase *base_event = getEvent(name);

        if (base_event == nullptr)
        {
            throw std::runtime_error("Event not found: " + name);
        }

        base_event->removeHandler(handler_id);
    }

    template <typename... Args>
    void trigger(const std::string &name, Args... args)
    {
        EventBase *base_event = getEvent(name);

        Event<Args...> *event = dynamic_cast<Event<Args...> *>(base_event);
        if (event == nullptr)
        {
            throw std::runtime_error("Trigger type mismatch for event: " + name);
        }

        event->trigger(std::forward<Args>(args)...);
    }

    void process(const std::string &name)
    {
        EventBase *base_event = getEvent(name);

        if (base_event == nullptr)
        {
            throw std::runtime_error("Event not found: " + name);
        }

        base_event->process();
    }

    void processAll()
    {
        for (auto &pair : events_)
        {
            pair.second->process();
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<EventBase>> events_;

    EventBase *getEvent(const std::string &name)
    {
        auto it = events_.find(name);

        if (it == events_.end())
        {
            return nullptr;
        }

        return it->second.get();
    }
};