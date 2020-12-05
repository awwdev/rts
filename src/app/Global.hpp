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
    inline MTEventBuffer eventBuffer;
    inline com::Array<Event, 10> events;

    inline f64  dt;
    inline i32  fps;
    inline bool hasSecondPassed;
    inline i32  windowWidth;
    inline i32  windowHeight;
}

///////////////////////////////////////////////////////////

inline bool HasEvent(app::EventEnum eventEnum)
{
    FOR_ARRAY(glo::events, i)
    {
        auto& ev = glo::events[i];
        if (ev.eventEnum == eventEnum)
            return true;
    }
    return false;
}

///////////////////////////////////////////////////////////

}//ns