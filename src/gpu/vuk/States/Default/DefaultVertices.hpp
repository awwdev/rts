#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/RenderData.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/DefaultRenderData.hpp"
#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct DefaultVertices
{
    VertexBuffer<DefaultVertex, gpu::VERTEX_COUNT_MAX> vbo;
    IndexBuffer<u32, (u32)(gpu::VERTEX_COUNT_MAX * 1.5)> ibo;
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

    //!IBO CAN BE CREATED WITH PATTERN AND THEN BE BAKED!
    ibo.Append(0);
    ibo.Append(1);
    ibo.Append(2);
    ibo.Append(0);
    ibo.Append(2);
    ibo.Append(3);
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
    //TODO array overload and store whole array at once 
    auto& vertices = renderData.defaultRenderData.vertices;
    vbo.count = 0;
    FOR_ARRAY(vertices, i)
    {
        vbo.Append(vertices[i]);
    }
}

///////////////////////////////////////////////////////////

}//ns