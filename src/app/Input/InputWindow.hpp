#pragma once

#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct WindowInput
{
    enum State
    {
        None,
        Begin,
        Continued,
        End,
    };

    State moveState;
    State sizeState;

    i32 xpos;
    i32 ypos;
    i32 width;
    i32 height;

    bool shouldClose;

    void UpdateStates();
};

///////////////////////////////////////////////////////////

void WindowInput::UpdateStates()
{

}

///////////////////////////////////////////////////////////

}//ns