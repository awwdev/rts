#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Renderer/Context.hpp"
#include "gpu/vuk/Context/PhysicalExt.hpp"
#include <cstring>

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct Buffer
{
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory memory;
    void* memPtr;

    void Create(VkBufferUsageFlags, size_t, VkMemoryPropertyFlags);
    void Destroy();
    void Store(void const*, size_t, size_t offset = 0);
    void Map();
    void Unmap();
};

///////////////////////////////////////////////////////////

void Buffer::Create(VkBufferUsageFlags usage, size_t pSize, VkMemoryPropertyFlags memProps)
{
    VkBufferCreateInfo bufferInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = 0,
        .size                   = pSize,
        .usage                  = usage,
        .sharingMode            = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount  = 0,
        .pQueueFamilyIndices    = nullptr
    };
    VkCheck(vkCreateBuffer(g_devicePtr, &bufferInfo, nullptr, &buffer));

    AllocateMemory(buffer, memory, memProps);
}

///////////////////////////////////////////////////////////

void Buffer::Destroy()
{
    vkDestroyBuffer (g_devicePtr, buffer, GetVkAlloc());
    vkFreeMemory    (g_devicePtr, memory, GetVkAlloc()); //will unmap
    *this = {};
}

///////////////////////////////////////////////////////////

void Buffer::Store(void const* data, size_t size, size_t offset)
{
    std::memcpy((char*)memPtr + offset, data, size);
}

////////////////////////////////////////////////////////////

void Buffer::Map()
{
    VkCheck(vkMapMemory(g_devicePtr, memory, 0, VK_WHOLE_SIZE, 0, &memPtr));
}

////////////////////////////////////////////////////////////

void Buffer::Unmap()
{
    vkUnmapMemory(g_devicePtr, memory);
}

///////////////////////////////////////////////////////////

}//ns