#pragma once

#include "com/AtomicRingBuffer.hpp"
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
    InputWindow window;
    InputKey    key;
    InputMouse  mouse;
};

///////////////////////////////////////////////////////////

struct Inputs
{
    inline static com::AtomicRingBuffer<Input, 50> inputBuffer;

    inline static InputWindow   window;
    inline static InputKeyboard keyboard;
    inline static InputMouse    mouse;

    enum class ActiveLayer { Scene, UI };
    inline static ActiveLayer activeLayer;

    static void Update();
};  

///////////////////////////////////////////////////////////

void Inputs::Update()
{
    window.Advance();
    keyboard.Advance();
    mouse.Advance();

    auto buffer = inputBuffer.Read();
    FOR_ARRAY(buffer, i)
    {
        auto& input = buffer[i];
        switch(input.type)
        {
            case Input::Window:
            window.Update(input.window);
            break;

            case Input::Keyboard:
            keyboard.Update(input.key);
            break;

            case Input::Mouse:
            mouse.Update(input.mouse);
            break;
        }
    }    
}

///////////////////////////////////////////////////////////

}//ns