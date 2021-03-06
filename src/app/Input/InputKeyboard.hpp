#pragma once

#include "com/Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct InputKey
{
    i64 value;
    enum State : u8 { Down, Up } state;  
};

///////////////////////////////////////////////////////////

struct InputKeyboard
{
    enum KeyState
    {
        None,
        Pressed,
        Released,
        Held,
    };

    KeyState keys [128];
    com::Array<i64, 128> keysPressed;

    void Advance();
    void Update(InputKey const&);

    //helper
    bool IsKeyHeld(i32) const;
};

///////////////////////////////////////////////////////////

void InputKeyboard::Advance()
{
    FOR_C_ARRAY(keys, i)
    {
        auto& key = keys[i];
        if (key == InputKeyboard::Pressed)  
            key =  InputKeyboard::Held;
        if (key == InputKeyboard::Released)  
            key =  InputKeyboard::None;            
    }
    keysPressed.count = 0;
}

///////////////////////////////////////////////////////////

void InputKeyboard::Update(InputKey const& input)
{
    if (input.state == InputKey::Down) keys[input.value] = InputKeyboard::Pressed;
    if (input.state == InputKey::Up)   keys[input.value] = InputKeyboard::Released;
    keysPressed.Append(input.value);
}

///////////////////////////////////////////////////////////

bool InputKeyboard::IsKeyHeld(i32 ascii) const
{
    return 
        keys[ascii] == KeyState::Held || 
        keys[ascii] == KeyState::Pressed;    
}

///////////////////////////////////////////////////////////

}//ns