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
        Continued,
        End,
    };

    State sizeState = None;
    i32 width;
    i32 height;

    bool shouldClose;
    
    void Advance();
    void Update(InputWindow const&);
};

///////////////////////////////////////////////////////////

void InputWindow::Advance()
{
    if (sizeState == InputWindow::End)
        sizeState = InputWindow::None;
}

///////////////////////////////////////////////////////////

void InputWindow::Update(InputWindow const& input)
{
    shouldClose = input.shouldClose;
    sizeState = input.sizeState;
    if (sizeState != InputWindow::None)
    {
        width = input.width;
        height = input.height;
    }    
}

///////////////////////////////////////////////////////////

}//ns