#pragma once

#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/RenderDataPost.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct PostVertices
{
    using Vertex = VertexPost;

    VertexBuffer<Vertex, VERTEX_COUNT_MAX_POST> vbo;
    VkDeviceSize offsets = 0;

    static VkVertexInputBindingDescription   bindings   [1];
    static VkVertexInputAttributeDescription attributes [3];

    void Create(VkCommandPool);
    void Destroy();
    void Update(RenderDataPost&);
};

///////////////////////////////////////////////////////////

VkVertexInputBindingDescription PostVertices::bindings [1] =
{
    {
        .binding    = 0,
        .stride     = sizeof(Vertex),
        .inputRate  = VK_VERTEX_INPUT_RATE_VERTEX
    }
};

///////////////////////////////////////////////////////////

VkVertexInputAttributeDescription PostVertices::attributes [3] =
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
        .format     = VK_FORMAT_R32G32_SFLOAT,
        .offset     = offsetof(Vertex, tex),
    },
    {
        .location   = 2,
        .binding    = 0, 
        .format     = VK_FORMAT_R32_SINT,
        .offset     = offsetof(Vertex, blur),
    },
};

///////////////////////////////////////////////////////////

void PostVertices::Create(VkCommandPool pool)
{
    vbo.Create();
}

///////////////////////////////////////////////////////////

void PostVertices::Destroy()
{
    vbo.Destroy();
}

///////////////////////////////////////////////////////////

void PostVertices::Update(RenderDataPost& rd)
{
    vbo.Clear();
    vbo.Append(rd.vertices.data, rd.vertices.count);
}

///////////////////////////////////////////////////////////

}//ns