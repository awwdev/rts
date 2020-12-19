#pragma once

#include "app/Input/Input.hpp"
#include "com/AtomicRingBuffer.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct Inputs
{
    inline static com::AtomicRingBuffer<Input, 20> inputBuffer;

    inline static InputWindow   window;
    inline static InputKeyboard keyboard;
    inline static InputMouse    mouse;

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
            keyboard.Update(input.keyboard);
            break;

            case Input::Mouse:
            mouse.Update(input.mouse);
            break;
        }
    }    
}

///////////////////////////////////////////////////////////

}//ns