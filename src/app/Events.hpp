#pragma once

#include <mutex>

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

struct MTEventBuffer
{
    static constexpr auto EVENT_COUNT_MAX = 10;

    com::Array<Event, EVENT_COUNT_MAX> buffer;
    std::mutex bufferMutex;

    auto Poll() -> com::Optional<Event>;
    void Push(Event const&);
};

///////////////////////////////////////////////////////////

auto MTEventBuffer::Poll() -> com::Optional<Event>
{
    com::Optional<Event> ev;
    bufferMutex.lock();
    if (buffer.count > 0)
        ev = buffer.Pop();        
    bufferMutex.unlock();
    return ev;
}

///////////////////////////////////////////////////////////

void MTEventBuffer::Push(Event const& ev)
{
    bufferMutex.lock();
    if (buffer.Contains(ev) == nullptr)
        buffer.Append(ev);
    bufferMutex.unlock();
}

///////////////////////////////////////////////////////////

}//ns