#pragma once

#include "com/Types.hpp"
#include "com/SimpleArray.hpp"
#include "app/Events.hpp"

///////////////////////////////////////////////////////////

namespace mini::app::glo {

///////////////////////////////////////////////////////////

inline bool isAppRunning = true;
inline f64  dt;
inline i32  fps;
inline bool hasSecondPassed;
inline i32  windowWidth;
inline i32  windowHeight;
inline com::SimpleArray<Event, 10> events;

///////////////////////////////////////////////////////////

}//ns