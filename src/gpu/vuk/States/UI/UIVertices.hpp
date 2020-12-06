#pragma once

#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/RenderDataUI.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct UIVertices
{
    using Vertex = VertexUI;

    VertexBuffer<Vertex, VERTEX_COUNT_MAX_UI> vbo;
    VkDeviceSize offsets = 0;

    static VkVertexInputBindingDescription   bindings   [1];
    static VkVertexInputAttributeDescription attributes [3];

    void Create(VkCommandPool);
    void Destroy();
    void Update(RenderDataUI&);
};

///////////////////////////////////////////////////////////

VkVertexInputBindingDescription UIVertices::bindings [1] =
{
    {
        .binding    = 0,
        .stride     = sizeof(Vertex),
        .inputRate  = VK_VERTEX_INPUT_RATE_VERTEX
    }
};

///////////////////////////////////////////////////////////

VkVertexInputAttributeDescription UIVertices::attributes [3] =
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
    {
        .location   = 2,
        .binding    = 0, 
        .format     = VK_FORMAT_R32_UINT,
        .offset     = offsetof(Vertex, texId),
    },
};

///////////////////////////////////////////////////////////

void UIVertices::Create(VkCommandPool pool)
{
    vbo.Create();
}

///////////////////////////////////////////////////////////

void UIVertices::Destroy()
{
    vbo.Destroy();
}

///////////////////////////////////////////////////////////

void UIVertices::Update(RenderDataUI& rd)
{
    vbo.count = 0;
    //vbo.Append()
}

///////////////////////////////////////////////////////////

}//ns