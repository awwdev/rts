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
    void AddBlurQuad(com::Recti const&);

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

void RenderDataPost::AddBlurQuad(com::Recti const& rect)
{
    using namespace com;
    
    Vec2f uv0 { (f32) rect.x / app::Inputs::window.width, (f32) rect.y / app::Inputs::window.height };
    Vec2f uv1 { (f32) rect.x / app::Inputs::window.width, (f32)(rect.y + rect.h) / app::Inputs::window.height };
    Vec2f uv2 { (f32)(rect.x + rect.w) / app::Inputs::window.width, (f32)(rect.y + rect.h) / app::Inputs::window.height };
    Vec2f uv3 { (f32)(rect.x + rect.w) / app::Inputs::window.width, (f32) rect.y / app::Inputs::window.height };

    Vec2f p0 { uv0.x * 2 - 1, uv0.y * 2 - 1 };
    Vec2f p1 { uv1.x * 2 - 1, uv1.y * 2 - 1 };
    Vec2f p2 { uv2.x * 2 - 1, uv2.y * 2 - 1 };
    Vec2f p3 { uv3.x * 2 - 1, uv3.y * 2 - 1 };

    vertices.Append(p0, uv0, 1);
    vertices.Append(p1, uv1, 1);
    vertices.Append(p2, uv2, 1);
    vertices.Append(p0, uv0, 1);
    vertices.Append(p2, uv2, 1);
    vertices.Append(p3, uv3, 1);
}

///////////////////////////////////////////////////////////

void RenderDataPost::Clear()
{
    vertices.count = 3; //don't clear the fullscreen triangle    
}

///////////////////////////////////////////////////////////

}//ns