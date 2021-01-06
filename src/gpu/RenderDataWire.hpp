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
        auto r = (com::Rectf)rect;
        vertices.Append(r.p1.x, r.p1.y, col);
        vertices.Append(r.p2.x, r.p1.y, col);
        vertices.Append(r.p2.x, r.p1.y, col);
        vertices.Append(r.p2.x, r.p2.y, col);
        vertices.Append(r.p2.x, r.p2.y, col);
        vertices.Append(r.p1.x, r.p2.y, col);
        vertices.Append(r.p1.x, r.p2.y, col);
        vertices.Append(r.p1.x, r.p1.y, col);
    }
};

///////////////////////////////////////////////////////////

void RenderDataWire::Clear()
{
    vertices.count = 0;
}

///////////////////////////////////////////////////////////

}//ns