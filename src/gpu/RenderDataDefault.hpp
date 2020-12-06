#pragma once

#include "com/Vec.hpp"
#include "com/POD_Array.hpp"
#include "ecs/EntityID.hpp"
#include "com/Rect.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct PushConstantsDefault
{
    i32 windowWidth;
    i32 windowHeight;
};

///////////////////////////////////////////////////////////

struct UniformDefault
{
    Rectf rect;
    Col4f col;
    u32 texId;
};

static constexpr auto s = sizeof(UniformDefault);

///////////////////////////////////////////////////////////

struct RenderDataDefault
{
    com::POD_Array<UniformDefault, ecs::ENTITY_COUNT_MAX> ubo;
    void Clear();
};

///////////////////////////////////////////////////////////

void RenderDataDefault::Clear()
{
    ubo.count = 0;
}

///////////////////////////////////////////////////////////

}//ns