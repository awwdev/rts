#pragma once

#include "app/_Event.hpp"
#include "com/POD_Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::app2 {

///////////////////////////////////////////////////////////

struct EventDataWindow
{
    i32 xpos;
    i32 ypos;
    i32 width;
    i32 height;
};

///////////////////////////////////////////////////////////

struct EventDataMouse
{
    i32 xpos;
    i32 ypos;
};

///////////////////////////////////////////////////////////

struct Events
{
    inline static com::POD_Array<Key, 10> keys;
    inline static EventDataWindow window;
    inline static EventDataMouse mouse;
    inline static bool appShouldClose;
    inline static void Clear();
};

///////////////////////////////////////////////////////////

void Events::Clear()
{
    keys.count = 0;
    FOR_ARRAY(keys, i)
    {
        auto& key = keys[i];
        key.Update();
    }
}

///////////////////////////////////////////////////////////

//TODO using enum

}//ns