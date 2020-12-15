#pragma once

#include <atomic>
#include "app/Input/Input.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct InputBuffer
{
    inline static constexpr auto RING_BUFFER_MAX = 10;
    inline static Input ringBuffer [RING_BUFFER_MAX] {};

    inline static std::atomic<i8> wndThreadCounter;
    inline static std::atomic<i8> appThreadCounter;

    inline static void PushInput(Input const&); //wnd thread
    inline static void PollInputs(); //app thread

private:
    inline static void StoreEvent(Input const&); //app thread
};

///////////////////////////////////////////////////////////

void InputBuffer::PushInput(Input const& event)
{
    auto wndCount = wndThreadCounter.load(std::memory_order_relaxed);
    ringBuffer[wndCount] = event;
    wndCount = (wndCount + 1) % RING_BUFFER_MAX;
    wndThreadCounter.store(wndCount, std::memory_order_relaxed);
}

///////////////////////////////////////////////////////////

void InputBuffer::PollInputs()
{
    Inputs::UpdateStates();

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

void InputBuffer::StoreEvent(Input const& input)
{
    switch(input.type)
    {
        default: 
        com::PrintWarning("Event not handled in EventBuffer");
        break;
    }
}

///////////////////////////////////////////////////////////

}//ns