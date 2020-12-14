#pragma once

#include <atomic>

#include "com/Types.hpp"
#include "com/POD_Array.hpp"
#include "app/Events.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

namespace glo
{
    inline std::atomic<bool> isAppRunning = true;
    inline std::atomic<bool> isWndResized = false;
    inline std::atomic<bool> isWndMinMax  = false;
    inline EventBuffer eventBuffer;

    inline f64  dt;
    inline i32  fps;
    inline bool hasSecondPassed;
    inline std::atomic<i32> windowWidth;
    inline std::atomic<i32> windowHeight;

    inline std::atomic<i32> atomic_mouse_x;
    inline std::atomic<i32> atomic_mouse_y;
    inline i32 mouse_x;
    inline i32 mouse_y;

    static void UpdateMousePos()
    {
        mouse_x = atomic_mouse_x.load(std::memory_order_relaxed);
        mouse_y = atomic_mouse_y.load(std::memory_order_relaxed);
    }
}

///////////////////////////////////////////////////////////

inline bool HasEvent(app::EventEnum eventEnum)
{
    FOR_ARRAY(glo::eventBuffer.appBuffer, i)
    {
        auto const& ev = glo::eventBuffer.appBuffer[i];  
        if (ev.eventEnum == eventEnum)
            return true;
    }
    return false;
}

///////////////////////////////////////////////////////////

}//ns