#pragma once

#include "com/Vec.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu {

///////////////////////////////////////////////////////////

struct DefaultVertex
{
    Vec2f pos;
    Vec2f tex;
    Col4f col;
};

///////////////////////////////////////////////////////////

struct DefaultPushConstants
{
    i32 windowWidth;
    i32 windowHeight;
};

///////////////////////////////////////////////////////////

struct DefaultRenderData
{

};

///////////////////////////////////////////////////////////

}//ns