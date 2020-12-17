#pragma once

#include "app/Input/InputWindow.hpp"
#include "app/Input/InputKeyboard.hpp"
#include "app/Input/InputMouse.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct Input
{
    enum Type
    {
        Window, 
        Keyboard,
        Mouse,
    };

    Type type;
    //union
    //{
    //    InputWindow   window {};
    //    InputKeyboard keyboard;
    //    InputMouse    mouse;
    //};
};

///////////////////////////////////////////////////////////

}//ns