#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/RenderData.hpp"
#include "com/Types.hpp"
#include "ecs/EntityID.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct DefaultVertices
{
    VertexBuffer<VertexDefault, VERTEX_COUNT_MAX_DEFAULT> vbo;
    IndexBuffer<u32, (u32)(VERTEX_COUNT_MAX_DEFAULT * 1.5)> ibo;
    VkDeviceSize offsets = 0;

    static VkVertexInputBindingDescription   bindings   [1];
    static VkVertexInputAttributeDescription attributes [3];

    void Create(VkCommandPool);
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

VkVertexInputBindingDescription DefaultVertices::bindings [1] =
{
    {
        .binding    = 0,
        .stride     = sizeof(VertexDefault),
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
        .offset     = offsetof(VertexDefault, pos),
    },
    {
        .location   = 1,
        .binding    = 0, 
        .format     = VK_FORMAT_R32G32B32A32_SFLOAT,
        .offset     = offsetof(VertexDefault, col),
    },
    {
        .location   = 2,
        .binding    = 0, 
        .format     = VK_FORMAT_R32_UINT,
        .offset     = offsetof(VertexDefault, texId),
    },
};

///////////////////////////////////////////////////////////

void DefaultVertices::Create(VkCommandPool pool)
{
    vbo.Create();

    //IBO PATTERN
    ibo.Create();
    for(auto i = 0; i < ecs::ENTITY_COUNT_MAX * 4; i+=4)
    {
        ibo.Append(i + 0);
        ibo.Append(i + 1);
        ibo.Append(i + 2);
        ibo.Append(i + 0);
        ibo.Append(i + 2);
        ibo.Append(i + 3);
    }
    ibo.Bake(pool);
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
    
    auto& vertices = renderData.renderDataDefault.vertices;
    vbo.count = 0;
    vbo.Append(vertices.data, vertices.count);
}

///////////////////////////////////////////////////////////

//TODO better index buffer strategy? because pattern is so obvious

}//ns