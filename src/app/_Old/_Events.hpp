#pragma once

#include "app/_Old/_Event.hpp"
#include "com/POD_Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::app2 {

///////////////////////////////////////////////////////////

struct Events
{
    inline static com::POD_Array<MouseButton, 10> keys;
    inline static Window window;
    inline static MouseButton mouse;
    inline static bool appShouldClose;
    inline static void Clear();
};

///////////////////////////////////////////////////////////

void Events::Clear()
{
    keys.count = 0;
    FOR_ARRAY(keys, i) //! wrong
    {
        auto& key = keys[i];
        key.Update();
    }
    window.Update();
    mouse.Update();
}

///////////////////////////////////////////////////////////

//TODO using enum

}//ns