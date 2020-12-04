#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/RenderData.hpp"
#include "com/Types.hpp"
#include "ecs/EntityID.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct PostVertices
{
    VertexBuffer<PostVertex, POST_VERTEX_COUNT> vbo;
    VkDeviceSize offsets = 0;

    static VkVertexInputBindingDescription   bindings   [1];
    static VkVertexInputAttributeDescription attributes [2];

    void Create(VkCommandPool);
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

VkVertexInputBindingDescription PostVertices::bindings [1] =
{
    {
        .binding    = 0,
        .stride     = sizeof(PostVertex),
        .inputRate  = VK_VERTEX_INPUT_RATE_VERTEX
    }
};

///////////////////////////////////////////////////////////

VkVertexInputAttributeDescription PostVertices::attributes [2] =
{
    {
        .location   = 0,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32_SFLOAT,
        .offset     = offsetof(PostVertex, pos),
    },
    {
        .location   = 1,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32_SFLOAT,
        .offset     = offsetof(PostVertex, tex),
    },
};

///////////////////////////////////////////////////////////

void PostVertices::Create(VkCommandPool pool)
{
    vbo.Create();

    //fullscreen triangle
    auto uv0 = Vec2f { (0 << 1) & 2, 0 & 2 };
    auto uv1 = Vec2f { (1 << 1) & 2, 1 & 2 };
    auto uv2 = Vec2f { (2 << 1) & 2, 2 & 2 };
    auto p0  = Vec2f { uv0.x * 2 - 1, uv0.y * 2 - 1 };
    auto p1  = Vec2f { uv1.x * 2 - 1, uv1.y * 2 - 1 };
    auto p2  = Vec2f { uv2.x * 2 - 1, uv2.y * 2 - 1 };
    vbo.Append({ p0, uv0 });
    vbo.Append({ p1, uv1 });
    vbo.Append({ p2, uv2 });
}

///////////////////////////////////////////////////////////

void PostVertices::Destroy()
{
    vbo.Destroy();
}

///////////////////////////////////////////////////////////

void PostVertices::Update(RenderData& renderData)
{

}

///////////////////////////////////////////////////////////

}//ns