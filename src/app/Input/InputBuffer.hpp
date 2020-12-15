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

    inline static std::atomic<i8> atomicWriteCount;
    inline static i8 readCount;

    inline static void WriteInput(Input const&);
    inline static void ReadInputs();
private:
    inline static void StoreInput(Input const&);
};

///////////////////////////////////////////////////////////

void InputBuffer::WriteInput(Input const& event)
{
    auto writeCount = atomicWriteCount.load(std::memory_order_relaxed);
    ringBuffer[writeCount] = event;
    writeCount = (writeCount + 1) % RING_BUFFER_MAX;
    atomicWriteCount.store(writeCount, std::memory_order_relaxed);
}

///////////////////////////////////////////////////////////

void InputBuffer::ReadInputs()
{
    auto writeCount = atomicWriteCount.load(std::memory_order_relaxed);
    if (writeCount == readCount)
        return;

    auto delta = (writeCount > readCount)
        ? writeCount - readCount
        : writeCount + RING_BUFFER_MAX - readCount;

    for(auto i = 0; i < delta; ++i)
    {
        auto ringIdx = (readCount + i) % RING_BUFFER_MAX;
        auto& event = ringBuffer[ringIdx];
        StoreInput(event);
    }

    readCount = (readCount + delta) % RING_BUFFER_MAX;
}

///////////////////////////////////////////////////////////

void InputBuffer::StoreInput(Input const& input)
{
    switch(input.type)
    {
        case Input::Window:

        if (input.window.sizeState == app::WindowInput::Continued)
        {
            if (Inputs::window.sizeState == app::WindowInput::Begin)
                Inputs::window.sizeState  = app::WindowInput::Continued;
            if (Inputs::window.sizeState == app::WindowInput::None)
                Inputs::window.sizeState  = app::WindowInput::Begin;
        }
        if (input.window.sizeState == app::WindowInput::End)
            Inputs::window.sizeState = app::WindowInput::End;

        if (Inputs::window.sizeState == app::WindowInput::Begin || 
            Inputs::window.sizeState == app::WindowInput::Continued)
        {
            Inputs::window.width  = input.window.width;
            Inputs::window.height = input.window.height;
        }
        break;

        ///////////////////////////////////////////////////////////

        case Input::Keyboard:
        break;

        ///////////////////////////////////////////////////////////

        case Input::Mouse:
        break;
    }
}

///////////////////////////////////////////////////////////

//! what when wndThreadCount surpasses appThreadCount

}//ns