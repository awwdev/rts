#pragma once

#include "com/POD_Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct InputKeyboard
{
    enum Key
    {
        Escape,
        ENUM_END
    };

    enum KeyState
    {
        None,
        Pressed,
        Released,
        Held,
    };

    KeyState keys [Key::ENUM_END];
    com::POD_Array<Key, Key::ENUM_END> keysPressed;
};

///////////////////////////////////////////////////////////

}//ns