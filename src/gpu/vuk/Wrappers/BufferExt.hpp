#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/Buffer.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

enum class BufferExtType 
{ 
    UniformBuffer, 
    VertexBuffer,
    StorageBuffer,
    IndexBuffer,
};

///////////////////////////////////////////////////////////

struct BufferExt
{
    Buffer  cpuBuffer;
    Buffer  gpuBuffer;
    Buffer* activeBuffer;

    void Create();
};

///////////////////////////////////////////////////////////

void BufferExt::Create()
{
    cpuBuffer.Create(
        BUFFER_USAGE | VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        BYTE_SIZE,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    );
    cpuBuffer.Map();
    activeBuffer = &cpuBuffer;   
}

///////////////////////////////////////////////////////////

}//ns