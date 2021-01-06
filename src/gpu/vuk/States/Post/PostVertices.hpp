#pragma once

#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/SwapResource.hpp"
#include "gpu/RenderDataPost.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct VerticesPost
{
    using RD = RenderDataPost;
    SwapResource<VertexBuffer<RD::Vertex, RD::VERTEX_MAX>> vbo;
    VkDeviceSize offsets = 0;

    static VkVertexInputBindingDescription   bindings   [1];
    static VkVertexInputAttributeDescription attributes [3];

    void Create(VkCommandPool);
    void Destroy() { DestroySwapResource(vbo); }
    void Update(RD&, u32);
};

///////////////////////////////////////////////////////////

void VerticesPost::Create(VkCommandPool pool)
{
    vbo.count = g_contextPtr->swapchain.Count();
    FOR_ARRAY(vbo, i)
        vbo[i].Create();
}

///////////////////////////////////////////////////////////

VkVertexInputBindingDescription 
VerticesPost::bindings [1] =
{
    {
        .binding    = 0,
        .stride     = sizeof(RD::Vertex),
        .inputRate  = VK_VERTEX_INPUT_RATE_VERTEX
    }
};

///////////////////////////////////////////////////////////

VkVertexInputAttributeDescription 
VerticesPost::attributes [3] =
{
    {
        .location   = 0,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32_SFLOAT,
        .offset     = offsetof(RD::Vertex, pos),
    },
    {
        .location   = 1,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32_SFLOAT,
        .offset     = offsetof(RD::Vertex, tex),
    },
    {
        .location   = 2,
        .binding    = 0, 
        .format     = VK_FORMAT_R32_SINT,
        .offset     = offsetof(RD::Vertex, blur),
    },
};

///////////////////////////////////////////////////////////

void VerticesPost::Update(RD& rd, u32 swapIdx)
{
    vbo[swapIdx].Clear();
    vbo[swapIdx].Append(rd.vertices.data, rd.vertices.count);
}

///////////////////////////////////////////////////////////

}//ns