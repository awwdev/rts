#pragma once

#include "app/_Event.hpp"
#include "com/POD_Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::app2 {

///////////////////////////////////////////////////////////

enum class EventType
{
    WM_Size,
    WM_Move,
    WM_Quit,

    Keyboard,

    MB_Left,
    MB_Right,
    MB_Middle,
};

///////////////////////////////////////////////////////////

enum class KeyButtonState
{
    None,
    Pressed,
    Held,
    Released,
};

///////////////////////////////////////////////////////////

struct Key
{
    KeyButtonState state;
    u8 asciiValue;

    void Update()
    {
        if (state == KeyButtonState::Pressed)
            state =  KeyButtonState::Held;
        if (state == KeyButtonState::Released)
            state =  KeyButtonState::None;
    }
};

///////////////////////////////////////////////////////////

struct Event
{
    EventType type;
    union
    {
        struct { i32 x, y; } coord;
        Key key;
    };
};

///////////////////////////////////////////////////////////

}//ns