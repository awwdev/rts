#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/RenderData.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/DefaultVertex.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct DefaultVertices
{
    VertexBuffer<DefaultVertex, 1000> vbo;
    IndexBuffer<u32, 1000> ibo;
    VkDeviceSize offsets = 0;

    static VkVertexInputBindingDescription   bindings   [1];
    static VkVertexInputAttributeDescription attributes [3];

    void Create();
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

VkVertexInputBindingDescription DefaultVertices::bindings [1] =
{
    {
        .binding    = 0,
        .stride     = sizeof(DefaultVertex),
        .inputRate  = VK_VERTEX_INPUT_RATE_VERTEX
    }
};

///////////////////////////////////////////////////////////

VkVertexInputAttributeDescription DefaultVertices::attributes [3] =
{
    {
        .location   = 0,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32_SFLOAT,
        .offset     = offsetof(DefaultVertex, pos),
    },
    {
        .location   = 1,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32_SFLOAT,
        .offset     = offsetof(DefaultVertex, tex),
    },
    {
        .location   = 2,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32B32A32_SFLOAT,
        .offset     = offsetof(DefaultVertex, col),
    },
};

///////////////////////////////////////////////////////////

void DefaultVertices::Create()
{
    vbo.Create();
    ibo.Create();

    //test
    vbo.Append({ { 0.0,-0.5 }, {}, { 1, 0, 0, 1 } });
    vbo.Append({ {-0.5, 0.5 }, {}, { 0, 1, 0, 1 } });
    vbo.Append({ { 0.5, 0.5 }, {}, { 0, 0, 1, 1 } });
}

///////////////////////////////////////////////////////////

void DefaultVertices::Destroy()
{
    vbo.Destroy();
    ibo.Destroy();
}

///////////////////////////////////////////////////////////

void DefaultVertices::Update(RenderData& renderData)
{

}

///////////////////////////////////////////////////////////

}//ns