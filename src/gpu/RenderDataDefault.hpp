#pragma once

#include "com/Vec.hpp"
#include "com/POD_Array.hpp"
#include "ecs/EntityID.hpp"
#include "com/Rect.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

constexpr auto VERTEX_COUNT_MAX_DEFAULT = ecs::ENTITY_COUNT_MAX * 4;

///////////////////////////////////////////////////////////

struct VertexDefault
{
    Vec2f pos;
    Col4f col;
    u32   texId;
};

///////////////////////////////////////////////////////////

struct PushConstantsDefault
{
    i32 windowWidth;
    i32 windowHeight;
};

///////////////////////////////////////////////////////////

struct UniformDefault
{
    alignas(16) Rectf rect;
    alignas(16) Col4f col;
    alignas(16) u32 texId;
};

///////////////////////////////////////////////////////////

struct RenderDataDefault
{
    com::POD_Array<VertexDefault, VERTEX_COUNT_MAX_DEFAULT> vertices;
    com::POD_Array<UniformDefault, 1'000> ubo;
    void Clear();
};

///////////////////////////////////////////////////////////

void RenderDataDefault::Clear()
{
    vertices.count = 0;
    ubo.count = 0;
}

///////////////////////////////////////////////////////////

}//ns