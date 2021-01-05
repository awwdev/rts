#pragma once

#include "com/Vec.hpp"
#include "com/Color.hpp"
#include "com/Array.hpp"
#include "com/Rect.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

constexpr auto VERTEX_COUNT_MAX_WIRE = 300;

///////////////////////////////////////////////////////////

struct RenderDataWire
{
    struct VertexWire
    {
        com::Vec2f pos;
        com::Col4n col;
    };

    com::Array<VertexWire, VERTEX_COUNT_MAX_WIRE> vertices;
    void Clear();

    void AddRect(com::AbsRecti const& rect, com::Col4n col = com::Col4n{ 1.f, 1.f, 1.f, 1.f })
    {
        vertices.Append((f32)rect.v1.x, (f32)rect.v1.y, col);
        vertices.Append((f32)rect.v2.x, (f32)rect.v1.y, col);
        vertices.Append((f32)rect.v2.x, (f32)rect.v1.y, col);
        vertices.Append((f32)rect.v2.x, (f32)rect.v2.y, col);
        vertices.Append((f32)rect.v2.x, (f32)rect.v2.y, col);
        vertices.Append((f32)rect.v1.x, (f32)rect.v2.y, col);
        vertices.Append((f32)rect.v1.x, (f32)rect.v2.y, col);
        vertices.Append((f32)rect.v1.x, (f32)rect.v1.y, col);
    }
};

///////////////////////////////////////////////////////////

void RenderDataWire::Clear()
{
    vertices.count = 0;
}

///////////////////////////////////////////////////////////

}//ns