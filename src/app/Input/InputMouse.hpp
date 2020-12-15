#pragma once

#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct MouseInput
{
    enum Button
    {
        Left,
        Right, 
        Middle,
        ENUM_END
    };

    enum ButtonState
    {
        None,
        Pressed,
        Released,
        Held,
    };

    ButtonState buttons [Button::ENUM_END];
    i32 xpos;
    i32 ypos;
    i32 scroll;

    void UpdateStates();
};

///////////////////////////////////////////////////////////

void MouseInput::UpdateStates()
{

}

///////////////////////////////////////////////////////////

}//ns