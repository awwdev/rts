#pragma once

#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/SwapResource.hpp"
#include "gpu/RenderDataWire.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct VerticesWire
{
    using RD = RenderDataWire;
    using Vertex = RD::VertexWire;
    SwapResource<VertexBuffer<Vertex, VERTEX_COUNT_MAX_WIRE>> vbo;
    VkDeviceSize offsets = 0;

    static VkVertexInputBindingDescription   bindings   [1];
    static VkVertexInputAttributeDescription attributes [2];

    void Create(VkCommandPool);
    void Destroy();
    void Update(RD&, u32);
};

///////////////////////////////////////////////////////////

void VerticesWire::Create(VkCommandPool)
{
    vbo.count = g_contextPtr->swapchain.Count();
    FOR_ARRAY(vbo, i)
        vbo[i].Create();
}

///////////////////////////////////////////////////////////

void VerticesWire::Destroy()
{
    DestroySwapResource(vbo);
}

///////////////////////////////////////////////////////////

VkVertexInputBindingDescription 
VerticesWire::bindings [1] =
{
    {
        .binding    = 0,
        .stride     = sizeof(Vertex),
        .inputRate  = VK_VERTEX_INPUT_RATE_VERTEX
    }
};

///////////////////////////////////////////////////////////

VkVertexInputAttributeDescription 
VerticesWire::attributes [2] =
{
    {
        .location   = 0,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32_SFLOAT,
        .offset     = offsetof(Vertex, pos),
    },
    {
        .location   = 1,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32B32A32_SFLOAT,
        .offset     = offsetof(Vertex, col),
    },
};

///////////////////////////////////////////////////////////

void VerticesWire::Update(RD& rd, u32 imageIndex)
{
    vbo[imageIndex].Clear();
    vbo[imageIndex].Append(rd.vertices.data, rd.vertices.count);
}

///////////////////////////////////////////////////////////

}//ns