#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/Buffer.hpp"
#include "gpu/vuk/Renderer/CommandsExt.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

#define TEMPLATE template<VkBufferUsageFlagBits BUFFER_USAGE, typename T, auto N>
#define BUFFER_EXT BufferExt<BUFFER_USAGE, T, N>

///////////////////////////////////////////////////////////

TEMPLATE struct BufferExt
{
    static constexpr idx_t COUNT_MAX = N;
    static constexpr idx_t BYTE_SIZE = sizeof(T) * N;
    idx_t count = 0;

    Buffer  cpuBuffer;
    Buffer  gpuBuffer;
    Buffer* activeBuffer = nullptr;

    void Create();
    void Destroy();
    void Clear();
    void Bake(VkCommandPool);
    void Append(T const& element);
    void Append(T const* elements, idx_t elementCount);
    auto CurrentByteSize() const { return count * sizeof(T); }
};

///////////////////////////////////////////////////////////

TEMPLATE 
void BUFFER_EXT::Create()
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

TEMPLATE 
void BUFFER_EXT::Destroy()
{
    if (cpuBuffer.buffer) cpuBuffer.Destroy();
    if (gpuBuffer.buffer) gpuBuffer.Destroy();
    activeBuffer = nullptr;
    count = 0;
}

///////////////////////////////////////////////////////////

TEMPLATE 
void BUFFER_EXT::Clear()
{
    count = 0;
    memset(activeBuffer->memPtr, 0, BYTE_SIZE);
}

///////////////////////////////////////////////////////////

TEMPLATE 
void BUFFER_EXT::Append(T const& element)
{
    activeBuffer->Store((void*)&element, sizeof(T), CurrentByteSize());
    count += 1;
}

///////////////////////////////////////////////////////////

TEMPLATE 
void BUFFER_EXT::Append(T const* elements, idx_t elementCount)
{
    activeBuffer->Store((void*)elements, elementCount * sizeof(T), CurrentByteSize());
    count += elementCount;
}

///////////////////////////////////////////////////////////

TEMPLATE 
void BUFFER_EXT::Bake(VkCommandPool cmdPool)
{
    if (gpuBuffer.buffer) {
        VkCheck(vkQueueWaitIdle(g_contextPtr->device.queue));
        gpuBuffer.Destroy();
    }

    gpuBuffer.Create(
        BUFFER_USAGE | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        BYTE_SIZE,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
    );

    auto cmdBuffer = BeginCommands_OneTime(cmdPool);
    VkBufferCopy copyRegion 
    {
        .srcOffset = 0,
        .dstOffset = 0,
        .size = CurrentByteSize()
    };
    vkCmdCopyBuffer(cmdBuffer, cpuBuffer.buffer, gpuBuffer.buffer, 1, &copyRegion);
    EndCommands_OneTime(cmdBuffer, cmdPool);

    activeBuffer = &gpuBuffer;
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