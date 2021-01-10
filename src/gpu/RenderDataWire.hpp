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

    void AddRect(com::Recti const& rect, com::Col4n col = com::Col4n{ 1.f, 1.f, 1.f, 1.f })
    {
        auto p1 = (com::Vec2f) rect.pos;
        auto p2 = (com::Vec2f) rect.GetPos2();
        vertices.Append(p1.x, p1.y, col);
        vertices.Append(p2.x, p1.y, col);
        vertices.Append(p2.x, p1.y, col);
        vertices.Append(p2.x, p2.y, col);
        vertices.Append(p2.x, p2.y, col);
        vertices.Append(p1.x, p2.y, col);
        vertices.Append(p1.x, p2.y, col);
        vertices.Append(p1.x, p1.y, col);
    }
};

///////////////////////////////////////////////////////////

void RenderDataWire::Clear()
{
    vertices.count = 0;
}

///////////////////////////////////////////////////////////

}//ns