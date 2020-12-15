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
    union
    {
        WindowInput window;
        KeyboardInput keyboard;
        MouseInput mouse;
    };
};

///////////////////////////////////////////////////////////

struct Inputs
{
    inline static WindowInput   window;
    inline static KeyboardInput keyboard;
    inline static MouseInput    mouse;

    static void UpdateStates()
    {
        window.UpdateStates();
        keyboard.UpdateStates();
        mouse.UpdateStates();
        //TODO dont overwrite begin with continued
        //TODO but instead let that do updateStates (so no information loss)
    }
};  

///////////////////////////////////////////////////////////

}//ns