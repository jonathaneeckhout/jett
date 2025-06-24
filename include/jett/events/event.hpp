#pragma once

#include <unordered_map>
#include <queue>
#include <tuple>
#include <string>

#include "jett/events/event_base.hpp"

template <typename... Args>
class Event : public EventBase
{
public:
    Event(const std::string &name) : name_(name) {};

    int addHandler(void (*handler)(Args...))
    {
        int id = next_handler_id++;
        handlers_[id] = std::move(handler);
        return id;
    }

    void removeHandler(int id) override
    {
        handlers_.erase(id);
    }

    void trigger(Args... args)
    {
        queue_.emplace(std::make_tuple(std::forward<Args>(args)...));
    }

    void process() override
    {
        while (!queue_.empty())
        {
            auto args = std::move(queue_.front());
            queue_.pop();
            for (auto &[_, handler] : handlers_)
            {
                std::apply(handler, args);
            }
        }
    }

private:
    std::string name_;
    int next_handler_id = 1;
    std::unordered_map<int, void (*)(Args...)> handlers_;
    std::queue<std::tuple<Args...>> queue_;
};