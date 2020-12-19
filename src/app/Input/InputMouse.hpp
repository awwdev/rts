#pragma once

#include "com/Types.hpp"
#include "com/Vec.hpp"

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
    com::Vec2i pos;
    i32 scroll;

    void Advance();
    void Update(InputMouse const&);

    //helper
    bool IsPressedOrHeld(Button);
    bool IsPressed(Button);
    bool IsReleased(Button);
};

///////////////////////////////////////////////////////////

void InputMouse::Advance()
{
    FOR_C_ARRAY(buttons, i)
    {
        auto& button = buttons[i];
        if (button == Pressed)
            button =  Held;
        if (button == Released)
            button =  None;
    }
}

///////////////////////////////////////////////////////////

void InputMouse::Update(InputMouse const& input)
{
    pos = input.pos;
    FOR_C_ARRAY(input.buttons, i)
    {
        auto& button = input.buttons[i];
        if (button != None)
            buttons[i] = button;
    }
}

///////////////////////////////////////////////////////////

bool InputMouse::IsPressedOrHeld(Button btn)
{
    return buttons[btn] == Pressed || buttons[btn] == Held;     
}

///////////////////////////////////////////////////////////

bool InputMouse::IsPressed(Button btn)
{
    return buttons[btn] == Pressed;
}

///////////////////////////////////////////////////////////

bool InputMouse::IsReleased(Button btn)
{
    return buttons[btn] == Released;
}

///////////////////////////////////////////////////////////

}//ns