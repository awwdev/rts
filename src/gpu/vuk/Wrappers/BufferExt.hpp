#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/Buffer.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

#define TEMPLATE template<VkBufferUsageFlagBits BUFFER_USAGE, typename T, auto N>
#define BUFFER_EXT BufferExt<BUFFER_USAGE, T, N>

///////////////////////////////////////////////////////////

TEMPLATE struct BufferExt
{
    static constexpr auto BYTE_SIZE = sizeof(T) * N;
    idx_t count = 0;

    Buffer  cpuBuffer;
    Buffer  gpuBuffer;
    Buffer* activeBuffer = nullptr;

    void Create();
    void Destroy();
    void Bake();
    void Append(T const&);
};

///////////////////////////////////////////////////////////

TEMPLATE void BUFFER_EXT::Create()
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

TEMPLATE void BUFFER_EXT::Destroy()
{
    if (cpuBuffer.buffer) cpuBuffer.Destroy();
    if (gpuBuffer.buffer) gpuBuffer.Destroy();
    activeBuffer = nullptr;
}

///////////////////////////////////////////////////////////

TEMPLATE void BUFFER_EXT::Append(T const& element)
{
    activeBuffer->Store((void*)&element, sizeof(T), count * sizeof(T));
    count += 1;
}

///////////////////////////////////////////////////////////

TEMPLATE void BUFFER_EXT::Bake()
{

}

///////////////////////////////////////////////////////////

template<typename T, auto N>
using VertexBuffer = BufferExt<VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, T, N>;

template<typename T, auto N>
using IndexBuffer = BufferExt<VK_BUFFER_USAGE_INDEX_BUFFER_BIT, T, N>;

template<typename T, auto N>
using UniformBuffer = BufferExt<VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, T, N>;

template<typename T, auto N>
using StorageBuffer = BufferExt<VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, T, N>;

///////////////////////////////////////////////////////////

#undef TEMPLATE
#undef BUFFER_EXT

///////////////////////////////////////////////////////////

}//ns