#pragma once

#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct WindowInput
{
    enum State
    {
        SizeBegin,
        Sizing,
        SizeEnd,
        MoveBegin,
        Moving,
        MoveEnd,
        Quit
    };

    State state;
    i32 xpos;
    i32 ypos;
    i32 width;
    i32 height;
};

///////////////////////////////////////////////////////////

}//ns