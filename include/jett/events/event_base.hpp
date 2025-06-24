#pragma once

class EventBase
{
public:
    virtual ~EventBase() = default;
    virtual void process() = 0;
    virtual void removeHandler(int handler_id) = 0;
};