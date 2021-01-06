#pragma once

#include "com/Vec.hpp"
#include "com/Array.hpp"
#include "ecs/EntityID.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderDataPost
{
    static constexpr auto VERTEX_MAX = 300;

    struct Vertex
    {
        com::Vec2f pos;
        com::Vec2f tex;
        i32 blur;
    };

    struct PushConstants
    {
        i32 windowWidth;
        i32 windowHeight;
        i32 resolutionScale = 1;
    };

    com::Array<Vertex, VERTEX_MAX> vertices;
    void Clear();
    void AddBlurQuad(com::Recti const&);

    RenderDataPost();
};

///////////////////////////////////////////////////////////

RenderDataPost::RenderDataPost()
{
    //fullscreen triangle
    using namespace com;
    f32 scale = 1; //resolution scale
    auto uv0 = Vec2f { (0 << 1) & 2, 0 & 2 };
    auto uv1 = Vec2f { (1 << 1) & 2, 1 & 2 };
    auto uv2 = Vec2f { (2 << 1) & 2, 2 & 2 };
    auto p0  = Vec2f { uv0.x * 2 * scale - 1, uv0.y * scale * 2 - 1 };
    auto p1  = Vec2f { uv1.x * 2 * scale - 1, uv1.y * scale * 2 - 1 };
    auto p2  = Vec2f { uv2.x * 2 * scale - 1, uv2.y * scale * 2 - 1 };
    vertices.Append(Vertex{ p0, uv0, 0 });
    vertices.Append(Vertex{ p1, uv1, 0 });
    vertices.Append(Vertex{ p2, uv2, 0 });
}

///////////////////////////////////////////////////////////

void RenderDataPost::AddBlurQuad(com::Recti const& rect)
{
    using namespace com;
    
    Vec2f uv0 { (f32) rect.p1.x / app::Inputs::window.width, (f32) rect.p1.y / app::Inputs::window.height };
    Vec2f uv1 { (f32) rect.p1.x / app::Inputs::window.width, (f32)(rect.p1.y + rect.p2.y) / app::Inputs::window.height };
    Vec2f uv2 { (f32)(rect.p1.x + rect.p2.x) / app::Inputs::window.width, (f32)(rect.p1.y + rect.p2.y) / app::Inputs::window.height };
    Vec2f uv3 { (f32)(rect.p1.x + rect.p2.x) / app::Inputs::window.width, (f32) rect.p1.y / app::Inputs::window.height };

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