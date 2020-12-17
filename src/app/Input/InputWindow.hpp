#pragma once

#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct InputWindow
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
    bool minmax;

    void StoreState(InputWindow const&);
    void UpdateStates();
};

///////////////////////////////////////////////////////////

void InputWindow::StoreState(InputWindow const&)
{

}

///////////////////////////////////////////////////////////

void InputWindow::UpdateStates()
{
    if (sizeState == State::End)
        sizeState = State::None;
}

///////////////////////////////////////////////////////////

}//ns