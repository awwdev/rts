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

    void Create();
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void DefaultVertices::Create()
{
    vbo.Create();
    ibo.Create();
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