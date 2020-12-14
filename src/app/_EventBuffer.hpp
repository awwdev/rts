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
    inline static constexpr auto RING_BUFFER_MAX = 10;
    inline static Event ringBuffer [RING_BUFFER_MAX];

    inline static std::atomic<i8> wndThreadCounter;
    inline static std::atomic<i8> appThreadCounter;

    inline static void PushEvent(Event const&); //wnd thread
    inline static void PollEvents(); //app thread

private:
    inline static void StoreEvent(Event const&); //app thread
};

///////////////////////////////////////////////////////////

void EventBuffer::PushEvent(Event const& event)
{
    auto wndCount = wndThreadCounter.load(std::memory_order_relaxed);
    ringBuffer[wndCount] = event;
    wndCount = (wndCount + 1) % RING_BUFFER_MAX;
    wndThreadCounter.store(wndCount, std::memory_order_relaxed);
}

///////////////////////////////////////////////////////////

void EventBuffer::PollEvents()
{
    Events::Clear();

    auto wndCount = wndThreadCounter.load(std::memory_order_relaxed);
    auto appCount = appThreadCounter.load(std::memory_order_relaxed);

    if (wndCount == appCount)
        return;

    auto delta = (wndCount > appCount)
        ? wndCount - appCount
        : wndCount + RING_BUFFER_MAX - appCount;

    for(auto i = 0; i < delta; ++i)
    {
        auto ringIdx = (appCount + i) % RING_BUFFER_MAX;
        auto& event = ringBuffer[ringIdx];
        StoreEvent(event);
    }

    appCount = (appCount + delta) % RING_BUFFER_MAX;
    appThreadCounter.store(appCount, std::memory_order_relaxed);
}

///////////////////////////////////////////////////////////

void EventBuffer::StoreEvent(Event const& event)
{
    switch(event.type)
    {
        case EventType::Keyboard:
        Events::keys.Append(event.button);
        break;

        ///////////////////////////////////////////////////////////

        case EventType::WM_Move:
        break;

        ///////////////////////////////////////////////////////////

        case EventType::Mouse:
        //! has both movement and button
        break;

        ///////////////////////////////////////////////////////////

        case EventType::WM_Size:
        if (event.window.state == Window::Begin)
        {   
            Events::window.x  = event.window.x;
            Events::window.y = event.window.y;
        }
        Events::window.state = (app2::Window::State)event.window.state;
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