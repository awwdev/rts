#pragma once

#include <chrono>

#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct Time
{
    using clock_t = std::chrono::high_resolution_clock;
    using dur_t   = std::chrono::duration<f64>;

    inline static f64 dt;
    inline static i32 fps;
    inline static bool hasSecondPassed;

    static void Update();
    static void PrintFps();

private:
    inline static i32 frames;
    inline static clock_t::time_point t1 = clock_t::now();
    inline static f64 secTimer;
};

///////////////////////////////////////////////////////////

void Time::Update()
{
    auto t2 = clock_t::now();
    dur_t dur = t2 - t1;
    t1 = t2;
    dt = dur.count();
    secTimer += dt;
    frames += 1;
    hasSecondPassed = false;
    if (secTimer >= 1)
    {
        hasSecondPassed = true;
        secTimer -= 1;
        fps = frames;
        frames = 0;
    }
}

///////////////////////////////////////////////////////////

void Time::PrintFps()
{
    if (hasSecondPassed)
        com::Print("fps", fps, "dt", dt);
}

///////////////////////////////////////////////////////////

}//ns