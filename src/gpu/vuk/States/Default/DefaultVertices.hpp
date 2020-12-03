#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/RenderData.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/DefaultRenderData.hpp"
#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

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
        .format     = VK_FORMAT_R32G32_SINT,
        .offset     = offsetof(DefaultVertex, pos),
    },
    {
        .location   = 1,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32B32A32_SFLOAT,
        .offset     = offsetof(DefaultVertex, col),
    },
    {
        .location   = 2,
        .binding    = 0, 
        .format     = VK_FORMAT_R32_UINT,
        .offset     = offsetof(DefaultVertex, texId),
    },
};

///////////////////////////////////////////////////////////

void DefaultVertices::Create()
{
    vbo.Create();

    //IBO PATTERN
    ibo.Create();
    for(auto i = 0; i < 400; i+=4)
    {
        ibo.Append(i + 0);
        ibo.Append(i + 1);
        ibo.Append(i + 2);
        ibo.Append(i + 0);
        ibo.Append(i + 2);
        ibo.Append(i + 3);
    }
    ibo.Bake();
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