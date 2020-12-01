#pragma once

#include "com/Vec.hpp"
#include "com/Array.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu {

///////////////////////////////////////////////////////////

constexpr auto VERTEX_COUNT_MAX = 1000;

///////////////////////////////////////////////////////////

struct DefaultVertex
{
    Vec2f pos;
    Vec2f tex; //not necessary when tex array is fully used
    Col4f col;
    u32   texId;
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
    com::Array<DefaultVertex, VERTEX_COUNT_MAX> vertices;
};

///////////////////////////////////////////////////////////

}//ns