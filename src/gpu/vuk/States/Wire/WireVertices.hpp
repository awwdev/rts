#pragma once

#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/RenderDataWire.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct VerticesWire
{
    using RD = RenderDataWire;
    using Vertex = RD::VertexWire;
    VertexBuffer<Vertex, VERTEX_COUNT_MAX_WIRE> vbo;
    VkDeviceSize offsets = 0;

    static VkVertexInputBindingDescription   bindings   [1];
    static VkVertexInputAttributeDescription attributes [2];

    void Create(VkCommandPool)      { vbo.Create();  }
    void Destroy()                  { vbo.Destroy(); }
    void Update(RD&);
};

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

void VerticesWire::Update(RD& rd)
{
    vbo.Clear();
    vbo.Append(rd.vertices.data, rd.vertices.count);
}

///////////////////////////////////////////////////////////

}//ns