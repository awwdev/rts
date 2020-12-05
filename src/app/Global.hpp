#pragma once

#include <atomic>

#include "com/Types.hpp"
#include "com/Array.hpp"
#include "app/Events.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

namespace glo
{
    inline std::atomic<bool> isAppRunning = true;
    inline EventBuffer eventBuffer;

    inline f64  dt;
    inline i32  fps;
    inline bool hasSecondPassed;
    inline i32  windowWidth;
    inline i32  windowHeight;
}

///////////////////////////////////////////////////////////

inline bool HasEvent(app::EventEnum eventEnum)
{
    const idx_t count = glo::eventBuffer.count;
    for(idx_t i = 0; i < count; ++i)
    {
        auto& ev = glo::eventBuffer.buffer[i];  
        if (ev.eventEnum == eventEnum)
            return true;
    }
    return false;
}

///////////////////////////////////////////////////////////

}//ns