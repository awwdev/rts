#pragma once

#include <mutex>
#include <atomic>

#include "com/Types.hpp"
#include "com/Optional.hpp"
#include "com/Assert.hpp"
#include "com/Array.hpp"

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

struct EventBuffer
{
    static constexpr auto EVENT_COUNT_MAX = 10;
    Event buffer [EVENT_COUNT_MAX];
    std::atomic<idx_t> count = 0;

    void Append(Event const&);
    void Reset();
};

///////////////////////////////////////////////////////////

void EventBuffer::Append(Event const& ev)
{
    if (count + 1 >= EVENT_COUNT_MAX)
    {
        com::PrintWarning("event buffer exhausted");
        return;
    }
    buffer[count] = ev;
    count++;
}

///////////////////////////////////////////////////////////

void EventBuffer::Reset()
{
    count = 0;
}

///////////////////////////////////////////////////////////

}//ns