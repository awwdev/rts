#pragma once

#include <atomic>
#include "com/Types.hpp"
#include "com/Print.hpp"
#include "app/_Events.hpp"

///////////////////////////////////////////////////////////

namespace rts::app2 {

///////////////////////////////////////////////////////////

struct EventBuffer
{
    static constexpr auto RING_BUFFER_MAX = 10;
    Event ringBuffer [RING_BUFFER_MAX];

    std::atomic<i8> wndThreadCounter = 0;
    std::atomic<i8> appThreadCounter = 0;

    void PushEvent(Event const&); //wnd thread
    void PollEvents(); //app thread

private:
    void StoreEvent(Event const&); //app thread
};

///////////////////////////////////////////////////////////

void EventBuffer::PushEvent(Event const& event)
{

}

///////////////////////////////////////////////////////////

void EventBuffer::PollEvents()
{
    Events::Clear();

    auto wndCount = wndThreadCounter.load(std::memory_order_relaxed);
    auto appCount = appThreadCounter.load(std::memory_order_relaxed);

    auto delta = (wndCount > appCount)
        ? wndCount - appCount
        : wndCount + RING_BUFFER_MAX - appCount;

    for(auto i = 0; i < delta; ++i)
    {
        auto ringIdx = (appCount + i) % RING_BUFFER_MAX;
        auto& event = ringBuffer[ringIdx];
        StoreEvent(event);
    }
}

///////////////////////////////////////////////////////////

void EventBuffer::StoreEvent(Event const& event)
{
    switch(event.type)
    {
        case EventType::Keyboard:
        Events::keys.Append(event.key);
        break;

        ///////////////////////////////////////////////////////////

        case EventType::WM_Move:
        Events::window.xpos = event.coord.x;
        Events::window.ypos = event.coord.y;
        break;

        ///////////////////////////////////////////////////////////

        case EventType::WM_Size:
        Events::window.width = event.coord.x;
        Events::window.height = event.coord.y;
        break;

        ///////////////////////////////////////////////////////////

        case EventType::WM_Quit:
        Events::appShouldClose = true;
        break;

        ///////////////////////////////////////////////////////////

        default: 
        com::PrintWarning("Event not handled in EventBuffer");
        break;
    }
}

///////////////////////////////////////////////////////////

//TODO using enum

}//ns