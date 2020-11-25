#pragma once

#include <chrono>
#include "app/Global.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::com::dt {

///////////////////////////////////////////////////////////

using clock_t = std::chrono::high_resolution_clock;
using dur_t   = std::chrono::duration<f64>;

inline i32 frames;
inline clock_t::time_point t1 = clock_t::now();
inline f64 secTimer;

///////////////////////////////////////////////////////////

inline void UpdateTime()
{
    auto t2 = clock_t::now();
    dur_t dur = t2 - t1;
    t1 = t2;
    app::glo::dt = dur.count();
    secTimer += app::glo::dt;
    frames += 1;
    app::glo::hasSecondPassed = false;
    if (secTimer >= 1)
    {
        app::glo::hasSecondPassed = true;
        secTimer = 0;
        app::glo::fps = frames;
        frames = 0;
    }
}

///////////////////////////////////////////////////////////

inline void PrintFps()
{
    if (app::glo::hasSecondPassed)
        com::Print("fps", app::glo::fps, "dt", app::glo::dt);
}

///////////////////////////////////////////////////////////

}//ns