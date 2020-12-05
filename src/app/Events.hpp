#pragma once

#include <atomic>
#include "com/Types.hpp"
#include "com/Optional.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

enum class EventEnum
{
    WND_MOVE_SIZE,
    KEY_DOWN_ESCAPE,
    MB_LEFT_DOWN,
};

///////////////////////////////////////////////////////////

struct Event
{
    EventEnum eventEnum;
    i32 xpos;
    i32 ypos;

    bool operator==(Event const& other) const;
};

///////////////////////////////////////////////////////////

bool Event::operator==(Event const& other) const
{
    return this->eventEnum == other.eventEnum;
}

///////////////////////////////////////////////////////////

struct MTEventBuffer
{
    static constexpr auto EVENT_COUNT_MAX = 10;

    Event buffer [EVENT_COUNT_MAX]; 
    std::atomic<idx_t> count = 0;

    auto Poll() -> com::Optional<Event>;
    void Push(Event const&);
};

///////////////////////////////////////////////////////////

auto MTEventBuffer::Poll() -> com::Optional<Event>
{
    if (count > 0)
    {
        count--;
        return buffer[count];
    }    
    return {};
}

///////////////////////////////////////////////////////////

void MTEventBuffer::Push(Event const& ev)
{
    buffer[count] = ev;
    count++;
}

///////////////////////////////////////////////////////////

}//ns