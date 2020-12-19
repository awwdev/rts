#pragma once

#include "com/Vec.hpp"
#include "com/POD_Array.hpp"
#include "ecs/EntityID.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

constexpr auto VERTEX_COUNT_MAX_POST = 300;

///////////////////////////////////////////////////////////

struct VertexPost
{
    com::Vec2f pos;
    com::Vec2f tex;
    i32   blur;
};

///////////////////////////////////////////////////////////

struct PushConstantsPost
{
    i32 resolutionScale = 1;
};

///////////////////////////////////////////////////////////

struct RenderDataPost
{
    com::POD_Array<VertexPost, VERTEX_COUNT_MAX_POST> vertices;
    void Clear();

    RenderDataPost()
    {
        using namespace com;

        f32 scale = 1; //resolution scale
        auto uv0 = Vec2f { (0 << 1) & 2, 0 & 2 };
        auto uv1 = Vec2f { (1 << 1) & 2, 1 & 2 };
        auto uv2 = Vec2f { (2 << 1) & 2, 2 & 2 };
        auto p0  = Vec2f { uv0.x * 2 * scale - 1, uv0.y * scale * 2 - 1 };
        auto p1  = Vec2f { uv1.x * 2 * scale - 1, uv1.y * scale * 2 - 1 };
        auto p2  = Vec2f { uv2.x * 2 * scale - 1, uv2.y * scale * 2 - 1 };
        vertices.Append(VertexPost{ p0, uv0, 0 });
        vertices.Append(VertexPost{ p1, uv1, 0 });
        vertices.Append(VertexPost{ p2, uv2, 0 });
    }
};

///////////////////////////////////////////////////////////

void RenderDataPost::Clear()
{
    vertices.count = 3; //don't clear the fullscreen triangle    
}

///////////////////////////////////////////////////////////

}//ns