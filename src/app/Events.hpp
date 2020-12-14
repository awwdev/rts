#pragma once

#include <atomic>

#include "com/Types.hpp"
#include "com/Optional.hpp"
#include "com/Assert.hpp"
#include "com/POD_Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

enum class EventEnum
{
    WND_MOVESIZE,
    WND_MOVESIZE_END,
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
    Event wndRingBuffer [EVENT_COUNT_MAX];
    std::atomic<u32> wndThreadCount = 0;
    std::atomic<u32> appThreadCount = 0;
    com::POD_Array<Event, EVENT_COUNT_MAX> appBuffer;

    void Append(Event const&); //wnd thread
    void Poll(); //app thread
};

///////////////////////////////////////////////////////////

void EventBuffer::Poll()
{
    appBuffer.count = 0;

    u32 delta = wndThreadCount - appThreadCount;
    if (wndThreadCount < appThreadCount)
        delta = (wndThreadCount + EVENT_COUNT_MAX) - appThreadCount;

    //com::Print(wndThreadCount.load(), appThreadCount.load(), delta);

    for(u32 i = 0; i < delta; ++i)
    {
        appBuffer.Append(wndRingBuffer[appThreadCount]);
        appThreadCount++;
        appThreadCount = appThreadCount % EVENT_COUNT_MAX;
    }
}

///////////////////////////////////////////////////////////

void EventBuffer::Append(Event const& ev)
{
    wndRingBuffer[wndThreadCount] = ev;
    wndThreadCount++;
    wndThreadCount = wndThreadCount % EVENT_COUNT_MAX;
}

///////////////////////////////////////////////////////////

enum class MouseState : i32
{
    LeftButtonDown   = 1 << 0,
    RightButtonDown  = 1 << 1,
    MiddleButtonDown = 1 << 2,
};

///////////////////////////////////////////////////////////

}//ns