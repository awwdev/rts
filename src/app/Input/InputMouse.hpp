#pragma once

#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct InputMouse
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

    void StoreState(InputMouse const&);
    void UpdateStates();
};

///////////////////////////////////////////////////////////

void InputMouse::StoreState(InputMouse const&)
{
    
}

///////////////////////////////////////////////////////////

void InputMouse::UpdateStates()
{

}

///////////////////////////////////////////////////////////

}//ns