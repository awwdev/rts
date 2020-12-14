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
    Mouse,
};

///////////////////////////////////////////////////////////

struct Window
{
    enum State { Begin, Continued, End, None } state;
    enum Type  { Move, Size } type;
    i32 x;
    i32 y;

    void Update()
    {
        if (state == Begin)
            state =  Continued;
        if (state == End)
            state =  None;
    }
};

///////////////////////////////////////////////////////////

struct KeyboardKey
{
    enum State { Pressed, Released, Held, None } state;
    u8 asciiValue;

    void Update()
    {
        if (state == Pressed)
            state =  Held;
        if (state == Released)
            state =  None;
    }
};

///////////////////////////////////////////////////////////

struct MouseButton
{
    enum State { Pressed, Released, Held, None } state;
    enum Type { Left, Middle, Right } type;

    void Update()
    {
        if (state == Pressed)
            state =  Held;
        if (state == Released)
            state =  None;
    }
};

///////////////////////////////////////////////////////////

struct Event
{
    EventType type;
    union
    {
        MouseButton button;
        KeyboardKey key;   
        Window window;   
    };
};

///////////////////////////////////////////////////////////

}//ns