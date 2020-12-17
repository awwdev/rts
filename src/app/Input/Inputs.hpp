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
    //window.UpdateStates();
    //keyboard.UpdateStates();
    //mouse.UpdateStates();

    //switch(input.type)
    //{
    //    case Input::Window:   Inputs::window.StoreState(input.window); break;
    //    case Input::Mouse:    Inputs::mouse.StoreState(input.mouse); break;
    //    case Input::Keyboard: Inputs::keyboard.StoreState(input.keyboard); break;
    //}
}

///////////////////////////////////////////////////////////

}//ns