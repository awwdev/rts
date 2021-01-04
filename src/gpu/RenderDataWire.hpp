#pragma once

#include "com/Vec.hpp"
#include "com/Color.hpp"
#include "com/Array.hpp"

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

    RenderDataWire()
    {
        //test
        vertices.Append(com::Vec2f{32, 32}, com::Col4n{1, 1, 1, 1});
        vertices.Append(com::Vec2f{64, 32}, com::Col4n{1, 1, 1, 1});
    }
};

///////////////////////////////////////////////////////////

void RenderDataWire::Clear()
{
    vertices.count = 2; //! test
}

///////////////////////////////////////////////////////////

}//ns