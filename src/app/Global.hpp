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
    inline EventBuffer eventBuffer;

    inline f64  dt;
    inline i32  fps;
    inline bool hasSecondPassed;
    inline std::atomic<i32> windowWidth;
    inline std::atomic<i32> windowHeight;
}

///////////////////////////////////////////////////////////

inline bool HasEvent(app::EventEnum eventEnum)
{
    const idx_t count = glo::eventBuffer.count.load();
    for(idx_t i = 0; i < count; ++i)
    {
        auto const& ev = glo::eventBuffer.buffer[i];  
        if (ev.eventEnum == eventEnum)
            return true;
    }
    return false;
}

///////////////////////////////////////////////////////////

}//ns