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
    auto buffer = inputBuffer.Read();

    FOR_ARRAY(buffer, i)
    {
        auto& input = buffer[i];
        switch(input.type)
        {
            case Input::Window:
            break;

            case Input::Mouse:
            break;

            case Input::Keyboard:
            break;
        }
    }    
}

///////////////////////////////////////////////////////////

}//ns