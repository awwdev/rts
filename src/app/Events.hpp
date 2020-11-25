#pragma once

#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace mini::app {

///////////////////////////////////////////////////////////

enum class EventEnum
{
    WND_MOVE_SIZE,
    KEY_DOWN_ESCAPE,
};

///////////////////////////////////////////////////////////

struct Event
{
    EventEnum eventEnum;
    i32 xpos;
    i32 ypos;
    i32 width;
    i32 height;

    bool operator==(Event const& other) const;
};

////////////////////////////////////////////////////////////

bool Event::operator==(Event const& other) const
{
    return this->eventEnum == other.eventEnum;
}

///////////////////////////////////////////////////////////

}//ns